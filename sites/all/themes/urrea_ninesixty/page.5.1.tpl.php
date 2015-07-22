<?php
// $Id: page.tpl.php,v 1.1.2.2.4.2 2011/01/11 01:08:49 dvessel Exp $
?>

<div id="page" class="container-12 clearfix">
	<?php if ($is_front): ?>
	  <div id="site-header-home" class="grid-12 clearfix">
	
	<?php endif; ?>
  
    <div id="branding" class="grid-12 alpha omega clearfix">
      <?php if ($linked_logo_img): ?>
        <span id="logo" class="grid-3 alpha"><?php print $linked_logo_img; ?></span>
      <?php endif; ?>
      <?php if ($linked_site_name): ?>
        <h1 id="site-name" class="grid-11 omega clearfix"><?php print $linked_site_name; ?></h1>
      <?php endif; ?>
      <?php if ($site_slogan): ?>
        <div id="site-slogan" class="grid-3 omega"><?php print $site_slogan; ?></div>
      <?php endif; ?>
    </div>
    <?php if ($page['header']): ?>
      <div id="header-region" class="grid-8 omega clearfix">
        <?php print render($page['header']); ?>
      </div>
    <?php endif; ?>

    <?php if ($page['search_box']): ?>
      <div id="search-box" class="grid-6 prefix-6"><?php print render($page['search_box']); ?></div>
    <?php endif; ?>
  </div>

  <div id="site-subheader" class="clearfix">
  <?php if ($page['highlighted']): ?>
    <div id="highlighted" class="<?php print ns('grid-10', $page['header'], 7); ?>">
      <?php print render($page['highlighted']); ?>
    </div>
  <?php endif; ?>
  </div>
	  <div id="main" class="grid-12 clearfix">
    <?php print render($title_prefix); ?>
    <?php print render($title_suffix); ?>
    <?php if ($tabs): ?>
      <div class="tabs"><?php print render($tabs); ?></div>
    <?php endif; ?>
    <?php if ($is_admin):?>
    	<?php print $messages; ?>
    <?php endif; ?>
    <?php print render($page['help']); ?>
    
  	</div><!-- /main -->
  	<?php if ($is_front): ?>
    	<?php if ($page['slide_show']): ?>
    	<div id="slide-show-contain"class="grid-12">
      	<div id="slide-show" class="grid-8 push-2 alpha clearfix">
					<?php print render($page['slide_show']); ?>
      	</div>
      </div> <!-- /slide-show-contain -->
    	<?php endif; ?>
			<!-- / slide-show -->
      <div id="tryptic" class="grid-12 clearfix">
        <?php if ($page['tryptic_first']): ?>
          <div id="tryptic-first" class="grid-4 alpha clearfix">
            <?php print render($page['tryptic_first']);?>
          </div>
        <?php endif; ?>
        <?php if ($page['tryptic_middle']): ?>
          <div id="tryptic-middle" class="grid-4 clearfix">
            <?php print render($page['tryptic_middle']);?>
          </div>
        <?php endif; ?>
        <?php if ($page['tryptic_last']): ?>
          <div id="tryptic-last" class="grid-4 omega clearfix">
            <?php print render($page['tryptic_last']);?>
          </div>
        <?php endif; ?>
      </div><!-- /tryptics -->
    <?php endif; ?>

<?php if (!$is_front): ?>
  <div id="content-wrapper" class="grid-12 clearfix">
    <?php if ($page['sidebar_first']): ?>
      <div id="sidebar-left" class="grid-3 alpha clearfix">
        <?php print render($page['sidebar_first']); ?>
      </div>
    <?php endif; ?>
      <div id="main-content" class="region <?php print ns('grid-8 alpha', $page['sidebar_first'], 3); ?>">
			<!-- tabs & admin -->
      
      
        <?php if ($title): ?>
          <h1 class="title" id="page-title"><?php print $title; ?></h1>
        <?php endif; ?>
        <?php print render($page['content']); ?>
      </div>
    <?php if ($page['sidebar_second']): ?>
      <div id="sidebar-right" class="grid-4 omega clearfix">
        <?php print render($page['sidebar_second']); ?>
      </div>
    <?php endif; ?>
  </div>
<!--/content-wrapper-->
<?php endif; ?>
  <div id="inferiores" class="grid-12 clearfix">
    <?php if ($page['primum_inferiores']): ?>
      <div id="primum-inferiores" class="grid-3 alpha clearfix">
        <?php print render($page['primum_inferiores']);?>
      </div>
    <?php endif; ?>
    <?php if ($page['secundum_inferiores']): ?>
      <div id="secundum-inferiores" class="region <?php print ns('grid-6', $page['sidebar_second'], 1); ?>">
        <?php print render($page['secundum_inferiores']);?>
      </div>
    <?php endif; ?>
    <?php if ($page['tertia_inferiores']): ?>
      <div id="tertia-inferiores" class="region <?php print ns('grid-4', $page['tryptic_first'], 1); ?> omega">
        <?php print render($page['tertia_inferiores']);?>
      </div>
    <?php endif; ?>
  </div>

<!-- /inferiores -->

  <div id="footer-wrapper" class="grid-12 clearfix">
  	<div id="main-feed" class="grid-12 alpha omega clearfix"><?php print $feed_icons; ?></div>
    <?php if ($main_menu_links || $secondary_menu_links): ?>
      <div id="site-menu" class="region <?php print ns('grid-12', $page['sidebar_second'], 1); ?> alpha">
        <?php print $main_menu_links; ?>
        <?php print $secondary_menu_links; ?>
      </div>
    <?php endif; ?>
    <div id="footer" class="region <?php print ns('grid-4', $page['tryptic_first'], 1); ?> omega">
      <?php if ($page['footer']): ?>
        <?php print render($page['footer']); ?>
      <?php endif; ?>
    </div>
  </div>
</div>
