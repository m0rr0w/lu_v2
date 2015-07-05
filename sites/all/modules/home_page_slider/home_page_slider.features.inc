<?php
/**
 * @file
 * home_page_slider.features.inc
 */

/**
 * Implements hook_views_api().
 */
function home_page_slider_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_image_default_styles().
 */
function home_page_slider_image_default_styles() {
  $styles = array();

  // Exported image style: home_page_thumbs.
  $styles['home_page_thumbs'] = array(
    'label' => 'home_page_thumbs',
    'effects' => array(
      2 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => 54,
          'height' => '',
          'upscale' => 0,
        ),
        'weight' => 1,
      ),
    ),
  );

  return $styles;
}

/**
 * Implements hook_node_info().
 */
function home_page_slider_node_info() {
  $items = array(
    'book_review' => array(
      'name' => t('Book Review'),
      'base' => 'node_content',
      'description' => t('Us this type to add a review for a book.'),
      'has_title' => '1',
      'title_label' => t('Reviewer'),
      'help' => '',
    ),
    'books' => array(
      'name' => t('Books'),
      'base' => 'node_content',
      'description' => t('Use this content type to add new Books to the site.'),
      'has_title' => '1',
      'title_label' => t('Title of Book'),
      'help' => '',
    ),
    'calendar_events' => array(
      'name' => t('Calendar Events'),
      'base' => 'node_content',
      'description' => t('Use this content type to add Calendar Events to the site.'),
      'has_title' => '1',
      'title_label' => t('Title of Event'),
      'help' => '',
    ),
    'related_content' => array(
      'name' => t('Related Content - Images'),
      'base' => 'node_content',
      'description' => t('Use this content type to add new images to the Related Content sections.'),
      'has_title' => '1',
      'title_label' => t('Image Title'),
      'help' => '',
    ),
    'related_content_audio' => array(
      'name' => t('Related Content - Audio'),
      'base' => 'node_content',
      'description' => t('Use this content type to add new audio tracks to the Related Content sections.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'related_content_links' => array(
      'name' => t('Related Content - Links'),
      'base' => 'node_content',
      'description' => t('Use this content type to add new links to the Related Content sections.'),
      'has_title' => '1',
      'title_label' => t('Link Title'),
      'help' => '',
    ),
    'related_content_videos' => array(
      'name' => t('Related Content - Videos'),
      'base' => 'node_content',
      'description' => t('Use this content type to add new videos to the Related Content sections.'),
      'has_title' => '1',
      'title_label' => t('Video Title'),
      'help' => '',
    ),
    'simple_text' => array(
      'name' => t('Simple Text'),
      'base' => 'node_content',
      'description' => t('This is a simple text field that can go into either the Related Content column, or the Homepage Slider.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'teresita_landing_page' => array(
      'name' => t('Teresita - Landing page'),
      'base' => 'node_content',
      'description' => t('This contains the biography, images and any other text for the Teresita landing page.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
