/**
 */
;(function($){
	"use strict";
	
	$.fn.mytree = function(options){
		var defaults = {
			ulContainerClass : 'tree-navigation-ul',
			data : null, // look the sample，jsonarray，or remotejson url
			expand : 'none', // 'all','none','first','last'
		};
		defaults = $.extend(defaults,options);

		var $ul = this.find('ul.'+defaults.ulContainerId);
		if($ul.length != 0){
			return;
		}
		var $tree = $(this);
		
		var initList = function(data,ulclazz){
			var $ul = $('<ul></ul>').addClass(ulclazz).appendTo($tree);
			
			var recur = function(obj,$parent){
				if(obj instanceof Array){
					obj.forEach(function(v,k){
						recur(v,$parent);
					});
				}else{
					var $li = $('<li></li>').attr('data-id',obj.id).attr('data-title',obj.title).appendTo($parent);
					$('<div class="title"></div>').text(obj.title).appendTo($li);
					if(obj.children && obj.children.length > 0){
						$li.addClass('root');
						$('<span class="status open"></span>').prependTo($li);
						var $nul = $('<ul></ul>').appendTo($li);
						recur(obj.children,$nul);
					}else{
						$li.addClass('child');
					}
				}
			};
			recur(data, $ul);
			
			$ul.find('li.root div.title').click(function(){
				var $this = $(this);
				var $status = $this.siblings('span.status');
				if($status.hasClass('open')){
					$status.removeClass('open').addClass('close');
					$this.siblings('ul').hide();
				}else{
					$status.removeClass('close').addClass('open');
					$this.siblings('ul').show();
				}
			});
			$ul.find('li.root div.title').click();
			$ul.find('li.root span.status').click(function(){
				$(this).siblings('div.title').click();
			});
			
			var findPaths = function($nowli){
				var arrays = [];
				var $now = $nowli;
				while($now.length){
					arrays.push($now.attr('data-title'));
					$now = $now.closest('ul').closest('li');
				}
				return arrays;
			};
			$ul.find('li.child div.title').click(function(){
				var $this = $(this);
				if($this.not('.selected')){
					$ul.find('li.child div.title.selected').removeClass('selected');
					$this.addClass('selected');
					var paths = findPaths($this.closest('li.child'));
					$('.tree-event-aware').trigger('treeevent:child-selected',[paths]);
				}
			});
			
		};

		if(!defaults.data){
			return this;
		}else if(defaults.data instanceof Array){
			initList(defaults.data,defaults.ulContainerClass);
		}else if(typeof defaults.data == 'string'){
			$.ajax({
				url : defaults.data,
				dataType : 'json',
				type: 'GET',
				success : function(data){
					initList(data,defaults.ulContainerClass);
				},
				error : function(data){
					alert('error');
				}
			});
		}
	};
})($);
