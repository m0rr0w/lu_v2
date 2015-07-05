 

jQuery(document).ready(function($) {
// Display a welcome message on first visit, and set a cookie that expires in 1 day:
if (document.cookie.indexOf('visited=true') == -1) {
    var fiveMinutes = 1000*2/**60*24*/;        
		var expires = new Date((new Date()).valueOf() + fiveMinutes);
    document.cookie = "visited=true; expires="+expires.toUTCString();
			$('.front #block-views-splash-page-splash-page-block').show();
			$.fn.colorbox({inline:true,href:"#block-views-splash-page-splash-page-block",innerWidth:"800px", innerHeight:"800px",open:true});
 
			 $(document).bind('cbox_closed', function(){
            $('.front #block-views-splash-page-splash-page-block').hide();
    });
}
 
});

