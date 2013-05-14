window.algorithm = window.algorithm || {};
window.algorithm.sort = window.algorithm.sort || {};
window.algorithm.sort.length = window.algorithm.sort.length || 10;
window.algorithm.sort.BubbleSort = function() {
};

/**
 * 新定义BubbleSort的原型
 */
window.algorithm.sort.BubbleSort.prototype = {
	randomArray : function() {
		var len = window.algorithm.sort.length;
		var arr = [];
		var has = [];
		while (arr.length < len) {
			var rd = Math.random();
			var r = Math.floor(rd * 1023 * 511) % len;
			if (has[r] && has[r] == 1) {
				continue;
			}
			arr.push(r+1);
			has[r] = 1;
		}
		return arr;
	}
};
$(function() {
	var bs = new window.algorithm.sort.BubbleSort();
	var arr = bs.randomArray();
	var $ctnt = $(".content");
	for ( var i = 0; i < arr.length; i++) {
		var d = $('<div class="color-div"></div>');
		d.attr('data-value', arr[i]).text(arr[i]).attr('id','value-'+i);
		$ctnt.append(d);
	}
	$('.color-div').each(function(index) {
		var v = $(this).attr('data-value');
		var r = (v * 12345) % 256;
		var g = (v * 23456) % 256;
		var b = (v * 34567) % 256;
		$(this).css("background-color", "rgb(" + r + "," + g + "," + b + ")");
		$(this).css('line-height', v * 30 + "px");
		$(this).css('margin-top', (350 - v * 30) + "px");
		if(index == 3){
			$(this).css('border','dotted');
			$(this).css('background-color','');
		}
	});
	
	$(".block").animate({"left": "+=50px"}, "slow");
});
