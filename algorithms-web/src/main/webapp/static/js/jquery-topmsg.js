;(function($){
	$.fn.topmsg = function(){
		var $topmsg = $(this);
		$topmsg.find('span.closeit').click(function(){
			$topmsg.hide();
		});
		var processTopmsg = function($topmsg,msg,latency){
			$topmsg.find('div.msg').text(msg);
			$topmsg.show();
			setTimeout(function(){
				$topmsg.hide();
			},latency);
		};
		$topmsg.on('errormsg',function(e,msg){
			$(this).removeClass('infomsg');
			$(this).addClass('errormsg');
			processTopmsg($(this),msg,5000);
		});
		$topmsg.on('infomsg',function(e,msg){
			$(this).removeClass('errormsg');
			$(this).addClass('infomsg');
			processTopmsg($(this),msg,3000);
		});
		return $topmsg;
	};
})($);