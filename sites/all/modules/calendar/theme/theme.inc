<?php

/**
 * @file
 * Theme functions for the Calendar module.
 */

/**
 * Display a calendar navigation and links
 */
function template_preprocess_calendar_main(&$vars) {
  if (module_exists('calendar_multiday')) {
    return;
  }
  
  module_load_include('inc', 'calendar', 'includes/calendar');

  // Add some basic values to the view.
  calendar_basics($vars);

  $view     = $vars['view'];
  $displays = $view->date_info->display_types;

  $calendar_links = array();
  $base = array('attributes' => array('rel' => 'nofollow'));
  if (!empty($displays['year'])) {
    $calendar_links['calendar calendar-year'] = $base + array('title' => t('Year', array(), array('context' => 'datetime')), 'href' => date_real_url($view, 'year'));
  }
  if (!empty($displays['month'])) {
    $calendar_links['calendar calendar-month'] = $base + array('title' => t('Month', array(), array('context' => 'datetime')), 'href' => date_real_url($view, 'month'));
  }
  if (!empty($displays['week'])) {
    $calendar_links['calendar calendar-week'] = $base + array('title' => t('Week', array(), array('context' => 'datetime')), 'href' => date_real_url($view, 'week'));
  }
  if (!empty($displays['day'])) {
    $calendar_links['calendar calendar-day'] = $base + array('title' => t('Day', array(), array('context' => 'datetime')), 'href' => date_real_url($view, 'day'));
  }
  $vars['calendar_links'] = $calendar_links;

  // If the Date Popup module is enabled, add a popup date selector.
  if (!empty($view->date_info->calendar_popup)) {
    $vars['calendar_popup'] = '<div class="clear-block">' . calendar_date_select($view) . '</div>';
  }

  // If an 'Add new ... link is provided, add it here.
  // the query will bring the user back here after adding the node.
  if (!empty($view->date_info->calendar_date_link) 
  && (user_access("administer nodes") || user_access('create '. $view->date_info->calendar_date_link .' content'))) {
    $name = node_type_get_name($view->date_info->calendar_date_link);
    $href = 'node/add/' . str_replace('_', '-', $view->date_info->calendar_date_link);
    $query = drupal_get_query_parameters(array('destination' => $view->date_info->url));    
    $vars['calendar_links']['calendar calendar-add'] = $base + array(
      'title' => t('Add+'), 
      'href' => $href, 
      'query' => $query,
      );
  }

}

/**
 * Display a view as a calendar.
 * 
 * This preprocessor does all the work needed for all types of calendar
 * views and the template takes care of displaying links to related views.
 */
function template_preprocess_calendar(&$vars) {
  if (module_exists('calendar_multiday')) {
    return;
  }

  module_load_include('inc', 'calendar', 'includes/calendar');  

  // Add some basic values to the view.
  calendar_basics($vars);

  $view     = $vars['view'];

  // Make sure we only run through this function one time.
  if (!empty($view->date_info->calendar_processed)) {
    return;
  }

  $result   = (array) $view->result;
  $view->style_plugin->render_fields($result);
  $rendered_items = !empty($view->style_plugin->rendered_fields) ? $view->style_plugin->rendered_fields : array();
  $items = array();

  $calendar_fields = date_views_fields($view->base_table);
  $calendar_fields = array_keys($calendar_fields['alias']);

  // Try to figure out the 'id' for this collection of items.
  // The id field is often not a field but instead an 'additional field',
  // so this is cludgy.
  foreach ($result as $num => $row) {
    $keys = array_keys((array) $row);
    foreach ($keys as $key) {
      if (strlen($key) == 3 && substr($key, -2) == 'id' && !empty($row->$key)) {
        $id = $key;
      }
    }
  }

  foreach ($result as $num => $row) {
    $copy = clone($row);
    $items[$num] = new stdClass(); 
    $items[$num]->id = !empty($row->$id) ? $row->$id : NULL;
    $items[$num]->rendered = $rendered_items[$num];
    $items[$num]->raw = $copy;

    $items[$num]->calendar_fields = new stdClass();
    foreach ($row as $key => $value) {
      if (in_array($key, $calendar_fields)) {
        $items[$num]->calendar_fields->$key = $value;
      }
    }
  }
  
  $vars['display_type'] = $view->date_info->granularity;
  $vars['min_date_formatted'] = date_format($view->date_info->min_date, DATE_FORMAT_DATETIME);
  $vars['max_date_formatted'] = date_format($view->date_info->max_date, DATE_FORMAT_DATETIME);

  // Massage the resulting items into formatted calendar items.
  $items = calendar_build_nodes($view, $items);

  // Merge in items from other sources.
  foreach (module_implements('calendar_add_items') as $module) {
    $function = $module . '_calendar_add_items';
    if (function_exists($function)) {
      if ($feeds = $function($view)) {
        foreach ($feeds as $feed) {
          $items = $feed;
        }
      }
    }
  }
  $view->date_info->mini = isset($view->date_info->mini) ? $view->date_info->mini : $view->date_info->granularity == 'year';

  // Create the calendar day names and rows.
  $rows = calendar_build_calendar($view, $items);

  $vars['items'] = $items;
  $vars['rows'] = $rows;

  $view->date_info->calendar_processed = TRUE;
  $vars['view'] = $view;  
  $vars['mini'] = !empty($view->date_info->mini);
  $vars['block'] = !empty($view->date_info->block);
}

/**
 * Display a month view.
 */
function template_preprocess_calendar_month(&$vars) {
  // Add in all the $vars added by the main calendar preprocessor.
  template_preprocess_calendar($vars);
  $view = $vars['view'];
  $rows = $vars['rows'];

  if (empty($rows)) {
    $rows = array();
    $day_names = array();
  } 
  elseif (sizeof($rows) > 1) {
    $day_names = array_shift($rows);
  }
  else {
    $day_names = $rows;
    $rows = array();
  }

  $month_rows = $rows;
  foreach ($rows as $weekno => $row) {
    foreach ($row as $day => $data) {
      $cell = $data['data'];

      // If this cell is already rendered, like the weekno column,
      // move to the next item.
      if (!is_array($cell)) {
        $month_rows[$weekno][$day]['data'] = $cell;
        continue;
      }
      $data = $cell['datebox'];
      if ($cell['empty']) {
        $data .= $cell['empty'];
      }
      else {
        $data .= implode($cell['all_day']);
        foreach ($cell['items'] as $hour => $item) {
          $data .= implode($item);
        }
        $data .= $cell['link'];
      }
      if ($view->date_info->mini) {
        $month_rows[$weekno][$day]['data'] = $data;
      }
      else {
        $month_rows[$weekno][$day]['data'] = '<div class="inner">' . $data . '</div>';
      }
    }
  }

  $vars['rows'] = $month_rows;
  $vars['day_names'] = $day_names;

  $vars['display_type'] = $view->date_info->granularity;
  $vars['min_date_formatted'] = date_format($view->date_info->min_date, DATE_FORMAT_DATETIME);
  $vars['max_date_formatted'] = date_format($view->date_info->max_date, DATE_FORMAT_DATETIME);
}

/**
 * Display a mini month view.
 */
function template_preprocess_calendar_mini(&$vars) {
  // Add in all the $vars added by the main calendar preprocessor.
  template_preprocess_calendar_month($vars);

  $view = $vars['view'];
  $view->date_info->show_title = !empty($view->date_info->show_title) ? $view->date_info->show_title : FALSE;
  $vars['show_title'] = $view->date_info->show_title;
  $vars['view'] = $view;
}

/**
 * Display a year view.
 */
function template_preprocess_calendar_year(&$vars) {
  // Add in all the $vars added by the main calendar preprocessor.
  $vars['view']->date_info->style_with_weekno = FALSE;
  template_preprocess_calendar($vars);

  // Get the url of the year view and remove the year argument from it.
  // TODO clean this up in case there is another arg that looks like
  // the year to make sure only the year gets removed.
  $view = $vars['view'];
  $year = date_format($view->date_info->min_date, 'Y');

  // Construct a calendar for each month, adjusting the $view passed 
  // to the theme so it will produce the right results.  
  $view = clone($vars['view']);
  $rows = $vars['rows'];
  $months = array();
  foreach ($rows as $month => $month_rows) {
    $view->date_info->month = $month;
    $view->date_info->granularity = 'month';
    $view->date_info->mini = TRUE;
    $view->date_info->hide_nav = TRUE;
    $view->date_info->show_title = TRUE;
    $view->date_info->url = date_real_url($view, NULL, date_pad($year, 4) . '-' . date_pad($month));
    $view->date_info->min_date = new DateObject($view->date_info->year . '-' . date_pad($month) . '-01 00:00:00', date_default_timezone());
    $view->date_info->max_date = clone($view->date_info->min_date);
    date_modify($view->date_info->max_date, '+1 month');
    date_modify($view->date_info->max_date, '-1 second');
    $variables = array(
      'view' => $view, 
      'options' => $vars['options'], 
      'rows' => $month_rows,
    );
    $months[$month] = theme('calendar_mini', $variables);
  }
  $vars['months'] = $months;
  $vars['view']->date_info->hide_nav = FALSE;
  $vars['view']->date_info->granularity = 'year';

}

/**
 * Display a day view.
 */
function template_preprocess_calendar_day(&$vars) {
  // Add in all the $vars added by the main calendar preprocessor.
  $vars['view']->style_with_weekno = FALSE;
  template_preprocess_calendar($vars);

  $view = $vars['view'];
  $rows = $vars['rows'];

  $item_count = 0;
  $by_hour_count = 0;
  $grouping_field = $view->date_info->style_groupby_field;

  // If we're not grouping by time, move all items into the 'all day' array.
  if (empty($view->date_info->style_groupby_times)) {
    // Items are already grouped into times, so we need to process each time-group.
    foreach ($rows['items'] as $time => $items) {
      foreach ($items as $item) {
        $rows['all_day'][] = $item;
      }
    }
    $rows['items'] = array();
  }

  $columns = array();

  // Move all_day items into the right columns and render them.
  $grouped_items = array();
  foreach ($rows['all_day'] as $item) {
    if (isset($item->{$grouping_field})) {
      $column = $item->{$grouping_field};        
      $item->{$grouping_field} = ''; // Remove the grouping field from the results.
      if (!in_array($column, $columns)) {
        $columns[] = $column;
      }
    }
    else {
      $column = t('Items');
    }
    $theme = isset($item->calendar_node_theme) ? $item->calendar_node_theme : 'calendar_' . $view->date_info->granularity . '_node';
    $grouped_items[$column][] = theme($theme, 
      array(
        'node' => $item, 
        'view' => $view,
      ));
    $item_count++;
  }
  $vars['rows']['all_day'] = $grouped_items;

  // Moved timed items into the right columns and render them.
  $start_times = $view->date_info->style_groupby_times;
  $show_empty_times = $view->date_info->style_show_empty_times; 
  $end_start_time = '23:59:59';
  $start_time = array_shift($start_times);
  $next_start_time = count($start_times) ? array_shift($start_times) : $end_start_time;

  $grouped_items = array();
  foreach ($rows['items'] as $time => $items) {
    foreach ($items as $item) {
      if (isset($item->{$grouping_field})) {
        $column = $item->{$grouping_field};
        $item->{$grouping_field} = ''; // Remove the grouping field from the results.
        if (!in_array($column, $columns)) {
          $columns[] = $column;
        }
      }
      else {
        $column = t('Items');
      }
      // Find the next time slot and fill it. Populate the skipped
      // slots if the option to show empty times was chosen.
      while ($time >= $next_start_time && $time < $end_start_time) {
        if ((!empty($show_empty_times)) && !array_key_exists($start_time, $grouped_items)) {
          $grouped_items[$start_time]['values'] = array();        
        }
        $start_time = $next_start_time;
        $next_start_time = count($start_times) ? array_shift($start_times) : $end_start_time;
      }
      $theme = isset($item->calendar_node_theme) ? $item->calendar_node_theme : 'calendar_' . $view->date_info->granularity . '_node';
      $variables = array(
        'node' => $item, 
        'view' => $view,
      );
      $grouped_items[$start_time]['values'][$column][] = theme($theme, $variables);
      $item_count++;
      $by_hour_count++;
    }
  }

  // Finish out the day's time values if we want to see empty times.
  if (!empty($show_empty_times)) {
    while ($start_time < $end_start_time) {
      if (!array_key_exists($start_time, $grouped_items)) {
        $grouped_items[$start_time]['values'] = array();        
      }
      $start_time = $next_start_time;
      $next_start_time = count($start_times) ? array_shift($start_times) : $end_start_time;
    }
  }

  // Do the headers last, once we know what the actual values are.
  $i = 0;
  $start_times = array_keys($grouped_items);
  foreach ($start_times as $start_time) {
    $next_start_time = array_key_exists($i + 1, $start_times) ? $start_times[$i + 1] : '23:59:59';
    $variables = array(
      'start_time' => $start_time, 
      'next_start_time' => $next_start_time, 
      'curday_date' => $rows['date'],
    );
    $heading = theme('calendar_time_row_heading', $variables);
    $grouped_items[$start_time]['hour'] = $heading['hour'];
    $grouped_items[$start_time]['ampm'] = $heading['ampm']; 
    $i++;      
  }
  ksort($grouped_items);
  $vars['rows']['items'] = $grouped_items;

  if (empty($columns)) {
    $columns = array(t('Items'));
  }
  $vars['columns'] = $columns;

  $vars['agenda_hour_class'] = 'calendar-agenda-hour';
  $first_column_width = 10;

  if (empty($view->date_info->style_groupby_times)) {
    $vars['agenda_hour_class'] .= ' calendar-agenda-no-hours';
    $first_column_width = 1;
  }

  $vars['first_column_width'] = $first_column_width;
  if (count($columns)) {
    $vars['column_width'] = round((100 - $first_column_width)/count($columns));
  }
  else {
    $vars['column_width'] = (100 - $first_column_width);
  }
  $vars['item_count'] = $item_count;
  $vars['by_hour_count'] = $by_hour_count;
  return;
}

/**
 * Display a week view.
 */
function template_preprocess_calendar_week(&$vars) {
  // Add in all the $vars added by the main calendar preprocessor.
  $vars['view']->style_with_weekno = FALSE;
  template_preprocess_calendar($vars);

  $view = $vars['view'];
  $rows = $vars['rows'];
  $item_count = 0;
  $by_hour_count = 0;

  if (sizeof($rows) > 1) {
    $day_names = array_shift($rows);
  }
  else {
    $day_names = $rows;
    $rows = array();
  }

  // Moved timed items into the right columns and render them.
  $show_empty_times = $view->date_info->style_show_empty_times; 
  $end_start_time = '23:59:59';

  $grouped_items = array();
  $vars['rows'] = $rows[0];
  foreach ($rows[0] as $weekno => $row) {
    $vars['rows'][$weekno] = $row['data'];

    // If we're not grouping by time, move all items into the 'all day' array.
    if (empty($view->date_info->style_groupby_times)) {
      foreach ($row['data']['items'] as $items) {
        foreach($items as $item) {
          $rows['all_day'][] = $item;
        }
      }
      $row['data']['items'] = array();
    }

    $columns[] = $weekno;
    $start_times = $view->date_info->style_groupby_times;
    $start_time = array_shift($start_times);
    $next_start_time = count($start_times) ? array_shift($start_times) : $end_start_time;
    foreach ($row['data']['all_day'] as $key => $item) {
      $theme = isset($item->calendar_node_theme) ? $item->calendar_node_theme : 'calendar_' . $view->date_info->granularity . '_node';
      $variables = array(
        'node' => $item,
        'view' => $view,
      );
      $vars['rows'][$weekno]['all_day'][$key] = theme($theme, $variables);
      $item_count++;
    }
    foreach ($row['data']['items'] as $time => $items) {
      foreach ($items as $item) {
        // Find the next time slot and fill it. Populate the skipped
        // slots if the option to show empty times was chosen.
        while ($time >= $next_start_time && $time < $end_start_time) {
          if (($show_empty_times) && !array_key_exists($start_time, $grouped_items)) {
            $grouped_items[$start_time]['values'][$weekno] = array();   
          }
          $start_time = $next_start_time;
          $next_start_time = count($start_times) ? array_shift($start_times) : $end_start_time;
        }
        $theme = isset($item->calendar_node_theme) ? $item->calendar_node_theme : 'calendar_' . $view->date_info->granularity . '_node';
        $variables = array(
          'node' => $item,
          'view' => $view,
        );
        $grouped_items[$start_time]['values'][$weekno][] = theme($theme, $variables);
        $item_count++; 
        $by_hour_count++; 
      }
    }

    // Finish out the day's time values if we want to see empty times.
    if ($show_empty_times) {
      while ($start_time < $end_start_time) {
        if (!array_key_exists($start_time, $grouped_items)) {
          $grouped_items[$start_time]['values'][$weekno] = array();        
        }
        $start_time = $next_start_time;
        $next_start_time = count($start_times) ? array_shift($start_times) : $end_start_time;
      }
    }
  }
  ksort($grouped_items);

  // Do the headers last, once we know what the actual values are.
  $i = 0;
  $start_times = array_keys($grouped_items);
  foreach ($start_times as $start_time) {
    $next_start_time = array_key_exists($i + 1, $start_times) ? $start_times[$i + 1] : '23:59:59';
    $variables = array(
      'start_time' => $start_time, 
      'next_start_time' => $next_start_time, 
      'curday_date' => $row['data']['date'],
    );
    $heading = theme('calendar_time_row_heading', $variables);
    $grouped_items[$start_time]['hour'] = $heading['hour'];
    $grouped_items[$start_time]['ampm'] = $heading['ampm'];       
  }

  $vars['items'] = $grouped_items;  

  $vars['day_names'] = $day_names;
  $vars['columns'] = $columns;
  $vars['start_times'] = $view->date_info->style_groupby_times;

  $vars['agenda_hour_class'] = 'calendar-agenda-hour';
  $first_column_width = 10;

  if (empty($view->date_info->style_groupby_times)) {
    $vars['agenda_hour_class'] .= ' calendar-agenda-no-hours';
    $first_column_width = 1;
  }
  $vars['item_count'] = $item_count;
  $vars['by_hour_count'] = $by_hour_count;
  return;
}

/**
 * Create the calendar date box.
 */
function template_preprocess_calendar_datebox(&$vars) {
  $date = $vars['date'];
  $view = $vars['view'];

  $vars['day'] = intval(substr($date, 8, 2));
  $force_view_url = !empty($view->date_info->block) ? TRUE : FALSE;
  $vars['url'] = date_real_url($view, NULL, $date, $force_view_url);
  $vars['link'] = !empty($view->date_info->display_types['day']) ? l($vars['day'], $vars['url']) : $vars['day'];
  $vars['granularity'] = $view->date_info->granularity;
  $vars['mini'] = $view->date_info->mini;

  if ($view->date_info->mini) {
    if (!empty($vars['selected'])) {
      $vars['class'] = 'mini-day-on';
    }
    else {
      $vars['class'] = 'mini-day-off';
    }
  }
  else {
    $vars['class'] = 'day';
  }
}

/**
 * Format an calendar node for display.
 */
function template_preprocess_calendar_node(&$vars) {
  $node = $vars['node'];
  $view = $vars['view'];
  $fields = array();
  foreach ($view->field as $name => $field) {
    $data = $node->rendered[$name];
    $label = $field->options['label'];

    // CCK has some special label options.
    if (!empty($field->content_field)) {
      switch ($field->options['label_type']) {
        case 'none':
          $label = '';
          break;
        case 'widget':
          $label = $field->content_field['widget']['label'];
          break;
      }
    }
    $fields[$name] = array(
      'id' => drupal_clean_css_identifier($node->id),
      'label' => $label,
      'data' => $data,
      );
  }
  $vars['fields'] = $fields;
  $vars['calendar_start'] = $node->calendar_start;
  $vars['calendar_end'] = $node->calendar_end;
  $vars['calendar_start_date'] = $node->calendar_start_date;
  $vars['calendar_end_date'] = $node->calendar_end_date;
}

/**
 * Format an calendar month node for display.
 */
function template_preprocess_calendar_month_node(&$vars) {
  template_preprocess_calendar_node($vars);
}

/**
 * Format an calendar month node for display.
 */
function template_preprocess_calendar_month_multiple_node(&$vars) {
  $view = $vars['view'];
  $curday = $vars['curday'];

  // get the year month and date
  $parts = explode('-', substr($curday, 0, 10));
  $year = $parts[0];
  $month = intval($parts[1]);
  $day = intval($parts[2]);

  // create the link to the day
  $vars['link'] = date_real_url($view, NULL, date_pad($year, 4) . '-' . date_pad($month) . '-' . date_pad($day));
}

/**
 * Format an calendar day node for display.
 */
function template_preprocess_calendar_day_node(&$vars) {
  template_preprocess_calendar_node($vars);
  $node = $vars['node'];
  // Remote items may have a teaser to show.
  if (!empty($node->remote) && !empty($node->teaser)) {
    $fields['teaser'] = '<div class="content">' . ($node->teaser) . "</div>\n";
  }
}

/**
 * Format an calendar week node for display.
 */
function template_preprocess_calendar_week_node(&$vars) {
  template_preprocess_calendar_node($vars);
}

/**
 * Format an calendar week node for display.
 */
function template_preprocess_calendar_week_multiple_node(&$vars) {
  $view = $vars['view'];
  $curday = $vars['curday'];

  // get the year month and date
  $parts = explode('-', substr($curday, 0, 10));
  $year = $parts[0];
  $month = intval($parts[1]);
  $day = intval($parts[2]);

  // create the link to the day
  $vars['link'] = date_real_url($view, NULL, date_pad($year, 4) . '-' . date_pad($month) . '-' . date_pad($day));
}

/**
 * Format the time row headings in the week and day view.
 */
function theme_calendar_time_row_heading($vars) {
  $start_time = $vars['start_time'];
  $next_start_time = $vars['next_start_time'];
  $curday_date = $vars['curday_date'];
  static $format_hour, $format_ampm;
  if (empty($format_hour)) {
    $format = variable_get('date_format_short', 'm/d/Y - H:i');
    $format_hour = str_replace(array('a', 'A'), '', date_limit_format($format, array('hour', 'minute')));
    $format_ampm = strstr($format, 'a') ? 'a' : (strstr($format, 'A') ? 'A' : '');
  }
  if ($start_time == '00:00:00' && $next_start_time == '23:59:59') {
    $hour = t('All times');
  }
  elseif ($start_time == '00:00:00') {
    $date = date_create($curday_date . ' ' . $next_start_time);
    $hour = t('Before @time', array('@time' => date_format($date, $format_hour)));
  }
  else {
    $date = date_create($curday_date . ' ' . $start_time);
    $hour = date_format($date, $format_hour);
  }
  if (!empty($date)) {
    $ampm = date_format($date, $format_ampm);
  }
  else {
    $ampm = '';
  }
  return array('hour' => $hour, 'ampm' => $ampm);
}

/**
 * Format a node stripe legend
 */
function theme_calendar_stripe_legend() {
  if (empty($GLOBALS['calendar_stripes'])) {
    return '';
  }
  $header = array(
      array('class' => 'calendar-legend', 'data' => t('Item')),
      array('class' => 'calendar-legend', 'data' => t('Key'))
      );
  $rows = array();
  $output = '';    
  foreach ((array) $GLOBALS['calendar_stripes'] as $label => $stripe) {
    if ($stripe) {
      $rows[] = array($label, '<div style="background-color:' . $stripe . ';color:' . $stripe . '" class="stripe" title="Key: ' . $label . '">&nbsp;</div>');
    }
  }
  if (!empty($rows)) {
    $variables = array(
      'header' => $header, 
      'rows' => $rows, 
      'attributes' => array('class' => 'mini calendar-legend'),
    );
    $output .= theme('table', $variables);
  }
  return $output;
}

/**
 * Format node stripes
 */
function theme_calendar_stripe_stripe($vars) {
  $node = $vars['node'];
  if (empty($node->stripe) || (!count($node->stripe))) {
    return;
  }
  $output = '';
  if (is_array($node->stripe_label)) {
    foreach ($node->stripe_label as $k => $stripe_label) {
      if (!empty($node->stripe[$k]) && !empty($stripe_label)) {
        $GLOBALS['calendar_stripes'][$stripe_label] = $node->stripe[$k];
        $output .= '<div style="background-color:' . $node->stripe[$k] . ';color:' . $node->stripe[$k] . '" class="stripe" title="Key: ' . $node->stripe_label[$k] . '">&nbsp;</div>' . "\n";
      }
    }
  }
  return $output;
}

/**
 * Format an empty day on a calendar
 *
 * @param day
 *   The day to display.
 */
function theme_calendar_empty_day($vars) {
  $curday = $vars['curday'];
  $view = $vars['view'];

  if ($view->date_info->calendar_type != 'day') {
    return '<div class="calendar-empty">&nbsp;</div>' . "\n";
  }
  else {
    return '<div class="calendar-dayview-empty">' . t('Empty day') . '</div>';
  }
}

/** @} End of addtogroup themeable */
