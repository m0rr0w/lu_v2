<?php
/**
 * @file
 * home_page_slider.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function home_page_slider_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'home_page_slider';
  $view->description = 'Displays all the selected content in a slider on the home page.';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Home Page Slider';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Home Page Slider';
  $handler->display->display_options['css_class'] = 'grid-7 push-1 alpha omega';
  $handler->display->display_options['use_more'] = TRUE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['use_more_text'] = 'read more...';
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'slideshow';
  $handler->display->display_options['style_options']['slideshow_type'] = 'views_slideshow_cycle';
  $handler->display->display_options['style_options']['slideshow_skin'] = 'default';
  $handler->display->display_options['style_options']['skin_info'] = array(
    'class' => 'default',
    'name' => 'Default',
    'module' => 'views_slideshow',
    'path' => '',
    'stylesheets' => array(),
  );
  $handler->display->display_options['style_options']['widgets']['top']['views_slideshow_pager']['weight'] = '1';
  $handler->display->display_options['style_options']['widgets']['top']['views_slideshow_pager']['type'] = 'views_slideshow_pager_fields';
  $handler->display->display_options['style_options']['widgets']['top']['views_slideshow_pager']['views_slideshow_pager_fields_fields'] = array(
    'field_book_cover' => 0,
    'field_rc_image' => 0,
    'field_blog_image' => 0,
    'title' => 0,
    'field_synopsis' => 0,
    'field_audio_desc' => 0,
    'field_rc_image_decr' => 0,
    'field_event_descrip' => 0,
    'field_rc_video_descr' => 0,
    'field_rc_link_decr' => 0,
    'field_blog_text' => 0,
    'field_rc_video_url' => 0,
    'field_rc_link' => 0,
    'field_audio_track' => 0,
    'field_event_date' => 0,
  );
  $handler->display->display_options['style_options']['widgets']['top']['views_slideshow_controls']['weight'] = '1';
  $handler->display->display_options['style_options']['widgets']['top']['views_slideshow_controls']['type'] = 'views_slideshow_controls_text';
  $handler->display->display_options['style_options']['widgets']['top']['views_slideshow_slide_counter']['weight'] = '1';
  $handler->display->display_options['style_options']['widgets']['bottom']['views_slideshow_pager']['weight'] = '1';
  $handler->display->display_options['style_options']['widgets']['bottom']['views_slideshow_pager']['type'] = 'views_slideshow_pager_fields';
  $handler->display->display_options['style_options']['widgets']['bottom']['views_slideshow_pager']['views_slideshow_pager_fields_fields'] = array(
    'field_book_cover' => 0,
    'field_rc_image' => 0,
    'field_blog_image' => 0,
    'title' => 0,
    'field_synopsis' => 0,
    'field_audio_desc' => 0,
    'field_rc_image_decr' => 0,
    'field_event_descrip' => 0,
    'field_rc_video_descr' => 0,
    'field_rc_link_decr' => 0,
    'field_blog_text' => 0,
    'field_rc_video_url' => 0,
    'field_rc_link' => 0,
    'field_audio_track' => 0,
    'field_event_date' => 0,
  );
  $handler->display->display_options['style_options']['widgets']['bottom']['views_slideshow_controls']['enable'] = 1;
  $handler->display->display_options['style_options']['widgets']['bottom']['views_slideshow_controls']['weight'] = '1';
  $handler->display->display_options['style_options']['widgets']['bottom']['views_slideshow_controls']['type'] = 'views_slideshow_controls_text';
  $handler->display->display_options['style_options']['widgets']['bottom']['views_slideshow_slide_counter']['weight'] = '1';
  $handler->display->display_options['style_options']['views_slideshow_cycle']['effect'] = 'scrollHorz';
  $handler->display->display_options['style_options']['views_slideshow_cycle']['transition_advanced'] = 1;
  $handler->display->display_options['style_options']['views_slideshow_cycle']['timeout'] = '0';
  $handler->display->display_options['style_options']['views_slideshow_cycle']['speed'] = '200';
  $handler->display->display_options['style_options']['views_slideshow_cycle']['delay'] = '0';
  $handler->display->display_options['style_options']['views_slideshow_cycle']['pause'] = 0;
  $handler->display->display_options['style_options']['views_slideshow_cycle']['action_advanced'] = 1;
  $handler->display->display_options['style_options']['views_slideshow_cycle']['start_paused'] = 0;
  $handler->display->display_options['style_options']['views_slideshow_cycle']['remember_slide_days'] = '1';
  $handler->display->display_options['style_options']['views_slideshow_cycle']['items_per_slide'] = '1';
  $handler->display->display_options['style_options']['views_slideshow_cycle']['cleartype'] = 0;
  $handler->display->display_options['style_options']['views_slideshow_cycle']['cleartypenobg'] = 0;
  $handler->display->display_options['row_plugin'] = 'semanticviews_fields';
  $handler->display->display_options['row_options']['skip_blank'] = 1;
  $handler->display->display_options['row_options']['semantic_html'] = array(
    'field_book_cover' => array(
      'element_type' => 'div',
      'class' => 'grid-2 alpha',
    ),
    'field_rc_image' => array(
      'element_type' => 'div',
      'class' => 'grid-2 alpha',
    ),
    'field_blog_image' => array(
      'element_type' => 'div',
      'class' => 'grid-2 alpha',
    ),
    'field_ter_image' => array(
      'element_type' => 'div',
      'class' => 'grid-2 alpha',
    ),
    'title' => array(
      'element_type' => 'h1',
      'class' => 'grid-4 omega slide-show-title',
    ),
    'field_synopsis' => array(
      'element_type' => 'div',
      'class' => 'grid-4 omega slide-show-text',
    ),
    'field_audio_desc' => array(
      'element_type' => 'div',
      'class' => 'grid-4 omega slide-show-text',
    ),
    'field_rc_image_decr' => array(
      'element_type' => 'div',
      'class' => 'grid-4 omega',
    ),
    'field_event_descript' => array(
      'element_type' => 'p',
      'class' => 'grid-4 omega slide-show-text',
    ),
    'field_rc_link_decr' => array(
      'element_type' => 'div',
      'class' => 'grid-4 omega slide-show-text',
    ),
    'field_blog_text' => array(
      'element_type' => 'div',
      'class' => 'grid-4 omega slide-show-text',
    ),
    'field_rc_video_url' => array(
      'element_type' => 'div',
      'class' => 'grid-4 omega',
    ),
    'field_rc_link' => array(
      'element_type' => 'div',
      'class' => 'grid-4 omega slide-show-link',
    ),
    'field_audio_track' => array(
      'element_type' => 'div',
      'class' => 'grid-4 omega',
    ),
    'field_event_date' => array(
      'element_type' => 'div',
      'class' => 'grid-4 omega slide-show-date',
    ),
    'body' => array(
      'element_type' => 'div',
      'class' => 'grid-4 omega slide-show-text',
    ),
    'field_simple_link' => array(
      'element_type' => 'div',
      'class' => 'grid-4 omega slide-show-link',
    ),
    'field_biography' => array(
      'element_type' => 'div',
      'class' => 'grid-4 omega slide-show-text',
    ),
  );
  /* Relationship: Nodequeue: Queue */
  $handler->display->display_options['relationships']['nodequeue_rel']['id'] = 'nodequeue_rel';
  $handler->display->display_options['relationships']['nodequeue_rel']['table'] = 'node';
  $handler->display->display_options['relationships']['nodequeue_rel']['field'] = 'nodequeue_rel';
  $handler->display->display_options['relationships']['nodequeue_rel']['required'] = TRUE;
  $handler->display->display_options['relationships']['nodequeue_rel']['limit'] = 1;
  $handler->display->display_options['relationships']['nodequeue_rel']['names'] = array(
    'home_page_slider' => 'home_page_slider',
  );
  /* Field: Content: Cover Image */
  $handler->display->display_options['fields']['field_book_cover']['id'] = 'field_book_cover';
  $handler->display->display_options['fields']['field_book_cover']['table'] = 'field_data_field_book_cover';
  $handler->display->display_options['fields']['field_book_cover']['field'] = 'field_book_cover';
  $handler->display->display_options['fields']['field_book_cover']['label'] = '';
  $handler->display->display_options['fields']['field_book_cover']['element_type'] = 'div';
  $handler->display->display_options['fields']['field_book_cover']['element_class'] = 'slide-image';
  $handler->display->display_options['fields']['field_book_cover']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_book_cover']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_book_cover']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['field_book_cover']['hide_alter_empty'] = FALSE;
  $handler->display->display_options['fields']['field_book_cover']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_book_cover']['settings'] = array(
    'image_style' => 'medium',
    'image_link' => 'content',
  );
  $handler->display->display_options['fields']['field_book_cover']['group_column'] = 'fid';
  /* Field: Content: Image */
  $handler->display->display_options['fields']['field_rc_image']['id'] = 'field_rc_image';
  $handler->display->display_options['fields']['field_rc_image']['table'] = 'field_data_field_rc_image';
  $handler->display->display_options['fields']['field_rc_image']['field'] = 'field_rc_image';
  $handler->display->display_options['fields']['field_rc_image']['label'] = '';
  $handler->display->display_options['fields']['field_rc_image']['element_type'] = 'div';
  $handler->display->display_options['fields']['field_rc_image']['element_class'] = 'slide-image';
  $handler->display->display_options['fields']['field_rc_image']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_rc_image']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_rc_image']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['field_rc_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_rc_image']['settings'] = array(
    'image_style' => 'medium',
    'image_link' => 'content',
  );
  $handler->display->display_options['fields']['field_rc_image']['group_column'] = 'fid';
  /* Field: Content: Blog Image */
  $handler->display->display_options['fields']['field_blog_image']['id'] = 'field_blog_image';
  $handler->display->display_options['fields']['field_blog_image']['table'] = 'field_data_field_blog_image';
  $handler->display->display_options['fields']['field_blog_image']['field'] = 'field_blog_image';
  $handler->display->display_options['fields']['field_blog_image']['label'] = '';
  $handler->display->display_options['fields']['field_blog_image']['element_type'] = 'div';
  $handler->display->display_options['fields']['field_blog_image']['element_class'] = 'slide-image';
  $handler->display->display_options['fields']['field_blog_image']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_blog_image']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_blog_image']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['field_blog_image']['hide_alter_empty'] = FALSE;
  $handler->display->display_options['fields']['field_blog_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_blog_image']['settings'] = array(
    'image_style' => 'medium',
    'image_link' => 'content',
  );
  $handler->display->display_options['fields']['field_blog_image']['group_column'] = 'fid';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_type'] = 'h3';
  $handler->display->display_options['fields']['title']['element_class'] = 'slide-title';
  /* Field: Content: Synopsis */
  $handler->display->display_options['fields']['field_synopsis']['id'] = 'field_synopsis';
  $handler->display->display_options['fields']['field_synopsis']['table'] = 'field_data_field_synopsis';
  $handler->display->display_options['fields']['field_synopsis']['field'] = 'field_synopsis';
  $handler->display->display_options['fields']['field_synopsis']['label'] = '';
  $handler->display->display_options['fields']['field_synopsis']['element_type'] = 'p';
  $handler->display->display_options['fields']['field_synopsis']['element_class'] = 'slide-show-text';
  $handler->display->display_options['fields']['field_synopsis']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_synopsis']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_synopsis']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['field_synopsis']['type'] = 'text_summary_or_trimmed';
  $handler->display->display_options['fields']['field_synopsis']['settings'] = array(
    'trim_length' => '200',
  );
  /* Field: Content: Description */
  $handler->display->display_options['fields']['field_audio_desc']['id'] = 'field_audio_desc';
  $handler->display->display_options['fields']['field_audio_desc']['table'] = 'field_data_field_audio_desc';
  $handler->display->display_options['fields']['field_audio_desc']['field'] = 'field_audio_desc';
  $handler->display->display_options['fields']['field_audio_desc']['label'] = '';
  $handler->display->display_options['fields']['field_audio_desc']['element_type'] = 'div';
  $handler->display->display_options['fields']['field_audio_desc']['element_class'] = 'slide-text';
  $handler->display->display_options['fields']['field_audio_desc']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_audio_desc']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_audio_desc']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['field_audio_desc']['type'] = 'text_trimmed';
  $handler->display->display_options['fields']['field_audio_desc']['settings'] = array(
    'trim_length' => '200',
  );
  /* Field: Content: Image Description */
  $handler->display->display_options['fields']['field_rc_image_decr']['id'] = 'field_rc_image_decr';
  $handler->display->display_options['fields']['field_rc_image_decr']['table'] = 'field_data_field_rc_image_decr';
  $handler->display->display_options['fields']['field_rc_image_decr']['field'] = 'field_rc_image_decr';
  $handler->display->display_options['fields']['field_rc_image_decr']['label'] = '';
  $handler->display->display_options['fields']['field_rc_image_decr']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_rc_image_decr']['hide_empty'] = TRUE;
  /* Field: Content: Event Description */
  $handler->display->display_options['fields']['field_event_descript']['id'] = 'field_event_descript';
  $handler->display->display_options['fields']['field_event_descript']['table'] = 'field_data_field_event_descript';
  $handler->display->display_options['fields']['field_event_descript']['field'] = 'field_event_descript';
  $handler->display->display_options['fields']['field_event_descript']['label'] = '';
  $handler->display->display_options['fields']['field_event_descript']['element_type'] = 'div';
  $handler->display->display_options['fields']['field_event_descript']['element_class'] = 'grid-3 alpha omega';
  $handler->display->display_options['fields']['field_event_descript']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_event_descript']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['field_event_descript']['hide_alter_empty'] = FALSE;
  $handler->display->display_options['fields']['field_event_descript']['type'] = 'text_plain';
  $handler->display->display_options['fields']['field_event_descript']['settings'] = array(
    'trim_length' => '300',
  );
  /* Field: Content: Link Description */
  $handler->display->display_options['fields']['field_rc_link_decr']['id'] = 'field_rc_link_decr';
  $handler->display->display_options['fields']['field_rc_link_decr']['table'] = 'field_data_field_rc_link_decr';
  $handler->display->display_options['fields']['field_rc_link_decr']['field'] = 'field_rc_link_decr';
  $handler->display->display_options['fields']['field_rc_link_decr']['label'] = '';
  $handler->display->display_options['fields']['field_rc_link_decr']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_rc_link_decr']['hide_empty'] = TRUE;
  /* Field: Content: Blog Text */
  $handler->display->display_options['fields']['field_blog_text']['id'] = 'field_blog_text';
  $handler->display->display_options['fields']['field_blog_text']['table'] = 'field_data_field_blog_text';
  $handler->display->display_options['fields']['field_blog_text']['field'] = 'field_blog_text';
  $handler->display->display_options['fields']['field_blog_text']['label'] = '';
  $handler->display->display_options['fields']['field_blog_text']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_blog_text']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['field_blog_text']['type'] = 'text_trimmed';
  $handler->display->display_options['fields']['field_blog_text']['settings'] = array(
    'trim_length' => '200',
  );
  /* Field: Content: Video URL */
  $handler->display->display_options['fields']['field_rc_video_url']['id'] = 'field_rc_video_url';
  $handler->display->display_options['fields']['field_rc_video_url']['table'] = 'field_data_field_rc_video_url';
  $handler->display->display_options['fields']['field_rc_video_url']['field'] = 'field_rc_video_url';
  $handler->display->display_options['fields']['field_rc_video_url']['label'] = '';
  $handler->display->display_options['fields']['field_rc_video_url']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_rc_video_url']['hide_empty'] = TRUE;
  /* Field: Content: Link */
  $handler->display->display_options['fields']['field_rc_link']['id'] = 'field_rc_link';
  $handler->display->display_options['fields']['field_rc_link']['table'] = 'field_data_field_rc_link';
  $handler->display->display_options['fields']['field_rc_link']['field'] = 'field_rc_link';
  $handler->display->display_options['fields']['field_rc_link']['label'] = '';
  $handler->display->display_options['fields']['field_rc_link']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_rc_link']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['field_rc_link']['click_sort_column'] = 'url';
  $handler->display->display_options['fields']['field_rc_link']['type'] = 'default';
  $handler->display->display_options['fields']['field_rc_link']['group_column'] = 'url';
  /* Field: Content: Audio track */
  $handler->display->display_options['fields']['field_audio_track']['id'] = 'field_audio_track';
  $handler->display->display_options['fields']['field_audio_track']['table'] = 'field_data_field_audio_track';
  $handler->display->display_options['fields']['field_audio_track']['field'] = 'field_audio_track';
  $handler->display->display_options['fields']['field_audio_track']['label'] = '';
  $handler->display->display_options['fields']['field_audio_track']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_audio_track']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['field_audio_track']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_audio_track']['group_column'] = 'fid';
  /* Field: Content: Event Date */
  $handler->display->display_options['fields']['field_event_date']['id'] = 'field_event_date';
  $handler->display->display_options['fields']['field_event_date']['table'] = 'field_data_field_event_date';
  $handler->display->display_options['fields']['field_event_date']['field'] = 'field_event_date';
  $handler->display->display_options['fields']['field_event_date']['label'] = '';
  $handler->display->display_options['fields']['field_event_date']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_event_date']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['field_event_date']['settings'] = array(
    'format_type' => 'long',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
    'show_repeat_rule' => 'show',
  );
  /* Field: Content: Body */
  $handler->display->display_options['fields']['body']['id'] = 'body';
  $handler->display->display_options['fields']['body']['table'] = 'field_data_body';
  $handler->display->display_options['fields']['body']['field'] = 'body';
  $handler->display->display_options['fields']['body']['label'] = '';
  $handler->display->display_options['fields']['body']['alter']['max_length'] = '100';
  $handler->display->display_options['fields']['body']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['body']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['body']['settings'] = array(
    'trim_length' => '600',
  );
  /* Field: Content: simple link */
  $handler->display->display_options['fields']['field_simple_link']['id'] = 'field_simple_link';
  $handler->display->display_options['fields']['field_simple_link']['table'] = 'field_data_field_simple_link';
  $handler->display->display_options['fields']['field_simple_link']['field'] = 'field_simple_link';
  $handler->display->display_options['fields']['field_simple_link']['label'] = '';
  $handler->display->display_options['fields']['field_simple_link']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_simple_link']['click_sort_column'] = 'url';
  $handler->display->display_options['fields']['field_simple_link']['type'] = 'default';
  $handler->display->display_options['fields']['field_simple_link']['group_column'] = 'url';
  /* Field: Content: Image */
  $handler->display->display_options['fields']['field_ter_image']['id'] = 'field_ter_image';
  $handler->display->display_options['fields']['field_ter_image']['table'] = 'field_data_field_ter_image';
  $handler->display->display_options['fields']['field_ter_image']['field'] = 'field_ter_image';
  $handler->display->display_options['fields']['field_ter_image']['label'] = '';
  $handler->display->display_options['fields']['field_ter_image']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ter_image']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['field_ter_image']['hide_alter_empty'] = FALSE;
  $handler->display->display_options['fields']['field_ter_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_ter_image']['settings'] = array(
    'image_style' => 'home_page_thumbs',
    'image_link' => 'content',
  );
  $handler->display->display_options['fields']['field_ter_image']['group_column'] = 'fid';
  /* Field: Content: Biography */
  $handler->display->display_options['fields']['field_biography']['id'] = 'field_biography';
  $handler->display->display_options['fields']['field_biography']['table'] = 'field_data_field_biography';
  $handler->display->display_options['fields']['field_biography']['field'] = 'field_biography';
  $handler->display->display_options['fields']['field_biography']['label'] = '';
  $handler->display->display_options['fields']['field_biography']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_biography']['alter']['text'] = '[field_biography-value]';
  $handler->display->display_options['fields']['field_biography']['alter']['max_length'] = '200';
  $handler->display->display_options['fields']['field_biography']['alter']['trim'] = TRUE;
  $handler->display->display_options['fields']['field_biography']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_biography']['hide_empty'] = TRUE;
  /* Sort criterion: Nodequeue: Position */
  $handler->display->display_options['sorts']['position']['id'] = 'position';
  $handler->display->display_options['sorts']['position']['table'] = 'nodequeue_nodes';
  $handler->display->display_options['sorts']['position']['field'] = 'position';
  $handler->display->display_options['sorts']['position']['relationship'] = 'nodequeue_rel';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 0;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;

  /* Display: Home Page Slider Block */
  $handler = $view->new_display('block', 'Home Page Slider Block', 'home_page_slider');
  $handler->display->display_options['block_description'] = 'Home Page Slider';
  $export['home_page_slider'] = $view;

  return $export;
}
