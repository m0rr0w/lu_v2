<?php

/**
 * @file
 * Display Suite 1 column template.
 */
?>
<div class="<?php print $classes;?> clearfix <?php print $ds_content_classes;?> urrea-blog">

  <?php if (isset($title_suffix['contextual_links'])): ?>
  <?php print render($title_suffix['contextual_links']); ?>
  <?php endif; ?>

  <?php print $ds_content; ?>
</div>