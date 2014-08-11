/**
 * 1、允许用户选择自己喜欢的背景颜色和透明度；<br>
 * 2、允许用户设置是否对其他人开放评注； <br>
 * 3、如果用户设置不对别人开放评注，则他自己也不能看到别人的评注；
 * 4、用户打开已经上传的PDF，基于MD5来判断是否已经存在，如果存在就可以和别人的评注关联起来；
 * 5、用户也可以（非常建议）搜索已经存在的文档，这样就可以直接和别人的学习及评注关联起来；
 * 6、用户每个文档的评注都有时间戳，某些用户关注的文档，一旦有新评注则自动通知这些用户；
 */
;
$(function() {
	var $commentDialog = $('#commentDialog');
	var $commentToolbar = $("#commentToolbar");
	
	//在特定位置打开某个元素
	$.fn.openAt = function(top, left) {
		this.css('top', top).css('left', left).removeClass('hidden');
		this.trigger('open');
		return this;
	};
	$.fn.close = function(){
		this.removeAttr('data-commentId');
		this.addClass('hidden');
		this.trigger('close');
		return this;
	};
	$.fn.isOpen = function() {
		return !this.hasClass('hidden');
	};
	
	/**
	 * 将div中存在的某个评论span删除掉
	 */
	$.fn.removeCommentSpanInDiv = function(commentId) {
		return $.each(this,function(){
			var $span = $(this).findCommentSpansInDiv(commentId);
			if($span.length > 0){
				$span.replaceWith($span.html());
				var newHtml = '';
				var contents = $(this).contents();
				for ( var i = 0; i < contents.length; i++) {
					if(contents[i].nodeType == Node.TEXT_NODE){
						newHtml += contents[i].data;
					}else{
						newHtml += $('<p>').append(contents[i]).html();
					}
				}
				$(this).html(newHtml);
			}
		});
	};
	/**
	 * 将原有的html切分为三部分，为了增加新的选区
	 * @html 原来的div中的html
	 * @leftOffset 新的需要切分的选区的初始字符空档偏移
	 * @rightOffset 新的需要切分的选区的结束字符空档偏移
	 * @return 如果可以切分，就返回三个元素的数组；如果存在冲突（有覆盖的时候）就返回null
	 */
	$.fn.splitDivHtmlToThreeParts = function(leftOffset, rightOffset) {
		var html = $(this).html();
		var mstr = '', lstr = '', rstr = '';
		var i = 0, j = 0;
		while (i < html.length) {
			var c = html.charAt(i);
			if (c == '<') {
				while (c != '>') {
					lstr += c;
					c = html.charAt(++i);
				}
			}else if (j >= leftOffset && j < rightOffset) {
				mstr += html.substring(i, i + rightOffset - leftOffset);
				rstr = html.substring(i + rightOffset - leftOffset);
				break;
			} else {
				j++;
			}
			lstr += c;
			i++;
		}
		return [ lstr, mstr, rstr ];
	};
	/**
	 * 是否为选中div
	 */
	$.fn.isSelectedDiv = function(comment){
		var index = $(this).index();
		return index >= comment.aDiv && index <= comment.fDiv;
	};
	/**
	 * 是否为选中的div中第一个
	 */
	$.fn.isFirstSelectedDiv = function(comment){
		var index = $(this).index();
		return index == comment.aDiv;
	};
	/**
	 * 是否为选中的div中最后一个
	 */
	$.fn.isLastSelectedDiv = function(comment){
		var index = $(this).index();
		return index == comment.fDiv;
	};
	
	/**
	 * 判断当前div是否被选中，如果被选中，在这个div上应该得到的起始和结束字符偏移量
	 * @return 数组[loffset,roffset]；如果当前div没有选中，则返回null
	 */
	$.fn.isSelectedDivAndReturnOffsets = function(comment){
		var $this = $(this);
		if($this.isSelectedDiv(comment)){
			var index = $this.index();
			var text = $this.text();
			var lOffset = index > comment.aDiv ? 0 : comment.aOffset;
			var rOffset = index < comment.fDiv ? text.length : comment.fOffset;
			return [lOffset,rOffset];
		}
		return null;
	};
	
	//找到最内层包裹数据的div
	function findLowestDivsInPage(pageId) {
		return $('#' + pageId).find('div.textLayer div');
	}
	
	//找到相关的评论span
	$.fn.findCommentSpansInDiv = function(commentId){
		if(!commentId){
			return this.find('span.commented');
		}
		return this.find('span.commented').filter('[data-commentId="'+commentId+'"]');
	};
	
	//看某个div下，是否包含了某些颜色的评论span，尽量选择不一样的
	$.fn.isChildSpansHasColor = function(colors, idx) {
		if(this.length > 0){
			$.each(this.findCommentSpansInDiv(), function() {
				if($(this).hasClass(colors[idx])) {
					idx++;
				}
			});
		}
		return idx;
	};
	
	/**
	 * 选择合适的颜色，不与相邻的元素、上下两行元素的颜色冲突，同时尽量保证使用最少的颜色
	 */
	$.fn.selectedAvailableColor = function(comment){
		var colors = ['bggreen', 'bgpink', 'bgyellow','bgyellowgreen', 'bgbrown',
		              'bgcoral','bgcrimson','bgdarkgoldenrod','bglightgray','bgplum','bgsilver' ];
		var idx = 0;
		this.each(function(){
			var $this = $(this);
			if($this.isSelectedDiv(comment)){
				while(idx < colors.length){//不能超出范围
					var now = idx;
					var $span = $this.findCommentSpansInDiv(comment.id);
					if($span.prev().hasClass(colors[idx]) || $span.next().hasClass(colors[idx])){//不与相邻的元素有相同颜色
						idx++;
					}
					if($this.isFirstSelectedDiv(comment)){
						idx = $this.prev().isChildSpansHasColor(colors,idx);//不与上一行相同
					}
					if($this.isLastSelectedDiv(comment)){
						idx = $this.next().isChildSpansHasColor(colors,idx);//不与下一行相同
					}
					if(now == idx){
						break;
					}
				}
			}
		});
		return idx == colors.length ? colors[idx - 1] : colors[idx]; //最后一个保留
	};

	/**
	 * 对被选择的文本div，计算选择区域，添加span并增加背景颜色
	 */
	$.fn.addNewSpanAndBackground = function(comment){
		//增加span元素
		this.each(function(){
			var $this = $(this);
			var lrOffsets = $this.isSelectedDivAndReturnOffsets(comment);
			if(lrOffsets){
				var strParts = $this.splitDivHtmlToThreeParts(lrOffsets[0],lrOffsets[1]);
				var $spanContainer = $('<span>').attr('data-commentId',comment.id);
				$spanContainer.addClass('commented').text(strParts[1]);
				var mstr = $('<p>').append($spanContainer).html();
				$this.html(strParts[0] + mstr  + strParts[2]);
			}
		});
		//选择颜色并增加
		var colorClass = this.selectedAvailableColor(comment);
		this.each(function(){
			var $this = $(this);
			if($this.isSelectedDiv(comment)){
				$this.findCommentSpansInDiv(comment.id).addClass(colorClass);
			}
		});
	};

	/**
	 * 对被选择的文本div，计算选择区域是否和原来已有的内容，在范围上冲突（有覆盖）
	 */
	$.fn.hasConflictWithExistedComments = function(obj) {
		// 这两个选择的元素并不是被DIV包裹着
		if (obj.apNode.tagName != 'DIV' || obj.fpNode.tagName != 'DIV') {
			return true;
		}
		// 同一个div内，只要判断这两个node是同一个node（即中间不可能有其他node划分开，因为全部是文本）
		if (obj.aDiv == obj.fDiv) {
			return obj.aNode != obj.fNode;
		}
		var acontents = $(obj.apNode).contents();
		var fcontents = $(obj.fpNode).contents();
		// 不同的node，那anode一定是占有从中间到结尾文本，而fnode占有的文本一定是从头开始到中间
		if (acontents.index(obj.aNode) != acontents.length - 1
				|| fcontents.index(obj.fNode) != 0) {
			return true;
		}
		var flag = false;
		this.each(function() {
			var $this = $(this);
			var index = $this.index();
			if (index > obj.aDiv && index < obj.fDiv) {// 前后两个div的已经判断了
				if ($this.findCommentSpansInDiv().length > 0) {// 中间那些div的文本肯定是全部被选中，如果有span在内，肯定有冲突了
					flag = true;
				}
			}
		});
		return flag;
	};
	
	/**
	 * 计算实际的字符空档偏移量(空档，是指字符与字符间的位置，有可能同一行中存在多个不冲突的评论）
	 */
	$.fn.calculateOffsetInDiv = function(node, offset) {
		// children()，不包括文本node，而$a.index()方法，也是在$a的父节点的children()中找$a的下标
		// 用contents()可以把所有node找到，包括文本和注释类型（这里不考虑注释）
		var $this = $(this);
		var contents = $this.contents();
		var nodeIndex = contents.index(node);
		for ( var i = 0; i < nodeIndex; i++) {
			offset += $(contents[i]).text().length;
		}
		return offset;
	};
	
	//利用range对象来提炼前后坐标，
	function extractDataFromRange(result,selection){
		var range = selection.getRangeAt(0);
		var obj = {};
		obj.aNode = range.startContainer;
		obj.fNode = range.endContainer;
		//页面id
		var pageId1 = $(obj.aNode).parents('div.page').attr('id');
		var pageId2 = $(obj.fNode).parents('div.page').attr('id');
		if(pageId1 != pageId2){
			result.error = "不支持跨两页的注释！";
			return null;
		}
		obj.pageId = pageId1;
		if(obj.aNode.nodeName == '#text'){
			obj.apNode = obj.aNode.parentNode;
			obj.aOffset = range.startOffset;
		}else{ //有可能整行文本都被选中，然后node就变成了DIV元素（而非DIV内部的文本区域），这样的情况需要主动找到div中的text元素
			obj.apNode = obj.aNode;
			obj.aNode = $(obj.apNode).contents()[0];
			obj.aOffset = 0;
		}
		if(obj.fNode.nodeName == '#text'){
			obj.fpNode = obj.fNode.parentNode;
			obj.fOffset = range.endOffset;
		}else{
			obj.fpNode = obj.fNode;
			obj.fNode = $(obj.fpNode).contents()[0];
			obj.fOffset = 0;
		}
		obj.aDiv = $(obj.apNode).index();
		obj.fDiv = $(obj.fpNode).index();
		//重新计算基于DIV（而非当前node本身）的字符空档偏移量
		obj.aOffset = $(obj.apNode).calculateOffsetInDiv(obj.aNode,obj.aOffset);
		obj.fOffset = $(obj.fpNode).calculateOffsetInDiv(obj.fNode,obj.fOffset);
		//有可能选中的偏移量正好是div最后一个字符的后边一个空档上，这样情况时那个div就没有任何字符被选中，也就没有意义；主动替换成下一个node的起始点
		if(obj.apNode.textContent.length == obj.aOffset){
			obj.aDiv++;
			obj.apNode = findLowestDivsInPage(obj.pageId)[obj.aDiv];
			obj.aNode = obj.apNode.childNodes[0];
			obj.aOffset = 0;
		}
		if(obj.fOffset == 0){
			obj.fDiv --;
			obj.fpNode = findLowestDivsInPage(obj.pageId)[obj.fDiv];
			obj.fNode = obj.fpNode.childNodes[obj.fpNode.childNodes.length -1];
			obj.fOffset = obj.fpNode.textContent.length;
		}
		//文本内容
		obj.str = range.toString();
		return obj;
	};
	
	/**
	 * 计算选择区域;<br>
	 * 1、选择方向有可能是反向的，需要交换start与end；
	 * 2、在同一个div中，可能已经存在之前的选择区域和span，并不允许两个区域相互覆盖；
	 * 3、在一个div中，如果已经存在span，那么这个div的内容是被分成多个子Node(而那个anchorOffset是这个子node内的偏移)，所以需要识别出来；
	 */
	function assembleComment(result,selection){
		var obj = extractDataFromRange(result,selection);
		if(obj == null){
			return result;
		}
		var $divs = findLowestDivsInPage(obj.pageId);
		if($divs.hasConflictWithExistedComments(obj)){
			result.error = '选区与原有选区存在冲突！';
			return result;
		}
		var docId = "";
		result.comment = PDFComments.initComment(docId,obj.pageId,obj.aDiv,obj.aOffset,obj.fDiv,obj.fOffset,obj.str);
		return result;
	};
	
	/**
	 * 选中某个区域: <br>
	 * 1、如果选择的内容太多，则需要忽略； <br>
	 * 2、如果选择的内容为空串，则需要忽略；<br>
	 * 3、选择的串有可能多次出现，需要准确判断位置； <br>
	 * 4、选择的串有可能和之前选择的区域冲突； <br>
	 * 5、一行内允许不冲突的多次选择存在； <br>
	 * 6、如果两个选择完全相邻，是否需要合并？<br>
	 * 7、一个选择跨越多个结点时，这是一个完整的对象，要么一起保留要么一起删除；
	 * 如果选择的区域，不是正常的textLayer内部（比如对话框内部），则不能初始化对应的comment
	 */
	function initCommentObjectBySelection(selection){
		var result = {
			comment : null,
			error : null
		};
		if (selection.rangeCount == 0){
			return null;
		}else if(selection.rangeCount > 1){
			result.error = '不能选择两个以上不连续区域！';
			return result;
		}
		var selectedStr = selection.toString();
		if(!selectedStr || selectedStr.length == 0){
			return null;
		}
		if(selectedStr.trim().length == 0){
			result.error = '空白字符无效！';
			return result;
		}else if(selectedStr.length > 500){
			result.error = '选择的字符数不能超过500个！';
			return result;
		}
		return assembleComment(result,selection);
	};
	
	/**
	 * 是否需要打开评论工具条。
	 */
	function needShowCommentToolbar(selection){
		if (selection.rangeCount == 0){
			return false;
		}else if(selection.rangeCount > 1){
			return false;
		}
		var selectedStr = selection.toString();
		if(!selectedStr || selectedStr.length == 0){
			return false;
		}
		if(selectedStr.trim().length == 0){
			return false;
		}
		// FIXME 如果选择的区域，不是正常的textLayer内部（比如对话框内部），则不能初始化对应的comment
		return true;
	};

	//考虑到屏幕可视范围
	$.fn.calculateAvailablePosition = function(top, left) {
		var obj = {
			top : top,
			left : left
		};
		var dwidth = $(document).width();
		var dheight = $(document).height();
		if (this.width() + left > dwidth) {
			obj.left = dwidth - this.width() - 10;
		}
		if (this.height() + top > dheight) {
			obj.top = dheight - this.height() - 10;
		}
		return obj;
	};
	
	// 打开对话框
	$commentDialog.open = function(comment, top, left) {
		this.attr('data-commentId', comment.id);
		var newPosition = this.calculateAvailablePosition(top, left);
		if (newPosition.top != top) {
			if ($commentToolbar.isOpen() && newPosition.top < top) {// 如果高度改变，那dialog不能盖住toolbar
				var offset = $commentToolbar.offset();
				newPosition.top = offset.top - $commentDialog.height() - 2;
			}
		}
		this.openAt(newPosition.top, newPosition.left);
		this.find('textarea').val('').focus().val(comment.comment);// 选中文本框并聚焦
	};
	
	$commentToolbar.open = function(top,left){
		var newPosition = this.calculateAvailablePosition(top,left);
		this.openAt(newPosition.top,newPosition.left);
	};
	
	$commentDialog.openByToolbar = function(comment){
		var offset = $commentToolbar.offset();
		var height = $commentToolbar.height();
		$commentDialog.open(comment, offset.top + height + 2, offset.left);
	};
	

	$commentToolbar.find('.commentSelected').click(function(e) {
		if ($commentToolbar.isOpen()) {
			var commentId = $commentToolbar.attr('data-commentId');
			if (commentId) {
				var comment = PDFComments.findComment(commentId);
				$commentDialog.openByToolbar(comment);
				return;
			}
		}
		var selection = document.getSelection();
		var commentResult = initCommentObjectBySelection(selection);
		if (commentResult == null) {
			$commentToolbar.close();
			return;
		} else if (commentResult.error) {
			alert(commentResult.error);
			return;
		}
		var comment = commentResult.comment;
		// 增加选择背景
		findLowestDivsInPage(comment.pageId).addNewSpanAndBackground(comment);
		// 选择区域
		selection.removeAllRanges();
		// 第一次主动保存
		PDFComments.saveComment(comment);
		// 打开窗口
		$commentToolbar.attr('data-commentId', comment.id);
		$commentDialog.openByToolbar(comment);
	});
	
	// 鼠标键提起之后，自动发现被选中的区域
	$(document).on('mouseup', function(e) {
		$commentToolbar.close();
		$commentDialog.close();
		if (needShowCommentToolbar(document.getSelection())) {
			$commentToolbar.open(e.pageY + 26, e.pageX - 22);
		}
	});
	$commentToolbar.on('mouseup', function(e) {
		e.stopPropagation();
	});
	$commentDialog.on('mouseup', function(e) {
		e.stopPropagation();
	});
	
	//绑定未来的span的打开事件
	$(document).on('click', 'span.commented', function(e) {
		var id = $(this).attr('data-commentId');
		var comment = PDFComments.findComment(id);
		$commentDialog.open(comment, e.pageY, e.pageX);
	});
	
	//保存并关闭
	$commentDialog.find('input.confirm').click(function() {
		var txt = $commentDialog.find('textarea').val();
		var commentId = $commentDialog.attr('data-commentId');
		PDFComments.updateComment(commentId, txt);
		$commentToolbar.close();
		$commentDialog.close();
	});

	//删除
	$commentDialog.find('input.delete').click(function(){
		var commentId = $commentDialog.attr('data-commentId');
		var comment = PDFComments.findComment(commentId);
		var $divs = findLowestDivsInPage(comment.pageId);
		$divs.removeCommentSpanInDiv(commentId);
		$commentToolbar.close();
		$commentDialog.close();
	});
	
	//关闭
	$(window).on('keyup',function(e){
		if(e.keyCode == 27){
			$commentToolbar.close();
			$commentDialog.close();
		}
	});
	
	// 重新渲染当前页面的选择区域
	$(window).on('scalechange',function() {
		var interval = null;
		var render = function() {
			var ok = false;
			var comments = PDFComments.getSelected();
			var count = comments.length;
			$.each(comments,function() {
				//增加选择背景
				findLowestDivsInPage(this.pageId).addNewSpanAndBackground(this);
				ok = true;
			});
			if (count == 0 || count > 0 && ok) {
				clearInterval(interval);
			}
		};
		interval = setInterval(render, 1000);
	});
});
