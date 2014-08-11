;(function($){
	$.fn.getValues = function(){
		var vs = [];
		$(this).find('ul li').each(function(){
			var v = parseInt($(this).attr('data-value'));
			vs.push({k : v, v : $(this)});
		});
		return vs;
	};
	$.fn.randomBackgroundColor = function(){
		var random = function(base){
			if(!base)base = 0;
			return parseInt((Math.random()*10000) % (256-base)) + base;
		};
		$(this).css("background-color", "rgb(" + random(200) + "," + random() + "," + random() + ")");
	};
	$.fn.sort = function(config){
		return this.each(function(){
			var $t = $(this);
			var myconf = $.extend({
				player : null,//播放器
				topmsg : null,//外部消息提醒
				tasks : [],	//未完成的任务
				status : 'original',//original,running,paused,finished
				type : null,//'bubble','insertion','selection','qsort','heapsort'
				swap : function(arrays,bidx,eidx){
					var t = arrays[bidx];
					arrays[bidx] = arrays[eidx];
					arrays[eidx] = t;
				},
				sort : function(){
					var as = $t.getValues();
					this.tasks = [];
					for(var i=as.length-1; i > 0;i--){
						for(var j=0;j<i;j++){
							var o = {
								1 : as[j],
								2 : as[j+1],
								swap : false,
								index : j,
								lastone : j+1 == i
							};
							if(as[j].k > as[j+1].k){
								this.swap(as,j,j+1);
								o.swap = true;
							}
							this.tasks.push(o);
						}
					}
				},
				draw : function(){
					var intervalId = null;
					var t = this;
					intervalId = setInterval(function(){
						if(t.tasks.length<=0 || t.status != 'running'){
							clearInterval(intervalId);
							if(t.tasks.length == 0){
								t.status = 'finished';
								setTimeout(function(){
									$t.find('li.swap').removeClass('swap');
									$t.find('li.ordered').removeClass('ordered');
								}, 500);
							}
							return;
						}
						var v = t.tasks.shift();
						var $a = $(v[1].v);
						var $b = $(v[2].v);
						var lastone = null;
						$t.find('li.swap').removeClass('swap');
						if(v.swap){
							$a.addClass('swap');
							$a.insertAfter($b);
							if(v.lastone){
								lastone = $a;
							}
						}else{
							$b.addClass('swap');
							if(v.lastone){
								lastone = $b;
							}
						}
						if(lastone){
							setTimeout(function(){
								$t.find('li.ordered').removeClass('ordered');
								lastone.addClass('ordered');
							}, 500);
						}
					}, 500);
				},
				start : function(){
					if(this.tasks.length <= 0 && (this.status == 'original' || this.status == 'finished')){
						this.sort();
					}
					this.status = 'running';
					this.draw();
					this.topmsg.trigger('infomsg',[this.status]);
				},
				stop : function(){
					this.status = 'finished';
					this.tasks = [];
					this.topmsg.trigger('errormsg',[this.status]);
				},
				pause : function(){
					this.status = 'paused';
					this.topmsg.trigger('infomsg',[this.status]);
				}
			},config);
			$('body').on('player-play',function(){
				myconf.start();
			});
			$('body').on('player-stop',function(){
				myconf.stop();
			});
			$('body').on('player-pause',function(){
				myconf.pause();
			});
			return $t;
		});
	};
})($);
