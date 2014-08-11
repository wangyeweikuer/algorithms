;(function($){
	$.fn.player = function(){
		var $t = $(this);
		var $play = $t.find('.play');
		var $pause = $t.find('.pause');
		var $stop = $t.find('.stop');
		$play.click(function(){
			$play.addClass('hide');
			$pause.removeClass('hide');
			$('body').trigger('player-play');
		});
		$pause.click(function(){
			$pause.addClass('hide');
			$play.removeClass('hide');
			$('body').trigger('player-pause');
		});
		$stop.click(function(){
			$play.removeClass('hide');
			$pause.addClass('hide');
			$('body').trigger('player-stop');
		});
		$('body').keypress(function(e){
			if(e.which == 32){
				if($play.not('.hide').length){
					$play.click();
				}else if($pause.not('.hide').length){
					$pause.click();
				}
			}
		});
		return $t;
	};
})($);
