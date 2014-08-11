window.algorithm = window.algorithm || {};
window.algorithm.sort = window.algorithm.sort || {};
window.algorithm.sort.length = window.algorithm.sort.length || 10;
window.algorithm.sort.BubbleSort = function() {};

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
	},
	sort : function(arrays,swap_callback){
		for(var i=0;i<arrays.length;i++){
			for(var j=i+1;j<arrays.length;j++){
				if(arrays[j] > arrays[j+1]){
					swap(arrays,j,j+1);
					swap_callback(arrays[j],arrays[j+1]);
				}
			}
		}
	},
	swap : function(arrays,bidx,eidx){
		var t = arrays[bidx];
		arrays[bidx] = arrays[eidx];
		arrays[eidx] = t;
	}
};
$(function() {
	var $player = $('.player').player();
	var $topmsg = $('.topmsg').topmsg();
	$('#title').on('treeevent:child-selected',function(e,paths){
		alert('yyy');
		var txt = '';
		paths = paths.reverse();
		while(paths.length){
			if(txt != ''){
				txt += ' >> ';
			}
			txt += paths.shift();
		}
		$(this).find('span').text(txt);
	});
	$("#algorithm-content").sort({
		player : $player,
		topmsg : $topmsg
	});
	$('#tree-navigation').mytree({
		data : '/static/js/myplugins/tree/data-example.json'
	});
});
