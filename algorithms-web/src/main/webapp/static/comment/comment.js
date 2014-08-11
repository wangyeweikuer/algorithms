window.PDFComments = window.PDFComments || {
	/**
	 * key是id，而value是comment对象：
	 * <pre>
	 * {
	 *   id:'11',
	 *   pageId:'page11',
	 *   aDiv:22,	//选择的div在其page中属于第几个div
	 *   aOffset:33, //字符空档偏移量，比如字符串"|a|b|c|d|e|f|j|"，'|'相当与空档，这个就是对应的字符空档偏移量，第一个为0
	 *   fDiv:44,
	 *   fOffset:55,
	 *   comment:'xxxxxxx'
	 * }
	 * </pre>
	 */
	_data : [],
	/** 随机生成主键	 */
	generateId : function(){
		var randStr = function(){
			return Math.random().toString(36);
		};
		return randStr()+'#'+randStr();
	},
	getSelected : function(){
		var ndata = [];
		for(a in this._data){
			ndata.push(this._data[a]);
		}
		return ndata;
	},
	/**
	 * 初始化评论对象
	 * @param docId 文档唯一标志符
	 * @param pageId 在文档的某个页面中
	 * @param aDiv 选择文本区域的起始div
	 * @param aOffset 起始div中字符开始位置
	 * @param fDiv 选择文本区域的结束div
	 * @param fOffset 结束div的结束字符前的位置
	 * @param comment 评论内容
	 */
	initComment : function(docId,pageId,aDiv,aOffset,fDiv,fOffset,comment){
		return {
			id : this.generateId(),
			docId : docId,
			pageId : pageId,
			aDiv : aDiv,
			aOffset : aOffset,
			fDiv : fDiv,
			fOffset : fOffset,
			comment : comment
		};
	},
	/** 查找评论 */
	findComment : function(id) {
		return this._data[id];
	},
	/** 保存评论(新增或者更新） */
	saveComment : function(comment){
		if(!this._data[comment.id]){
			this._count ++;
		}
		this._data[comment.id] = comment;
	},
	/** 根据生成的id删除实际内容	 */
	deleteComment : function(id){
		if(this._data[id]){
			this._count --;
		}
		delete this._data[id];
	},
	/** 更新评论 */
	updateComment : function(id,comment){
		if(this._data[id]){
			this._data[id].comment = comment;
		}
	}
};
