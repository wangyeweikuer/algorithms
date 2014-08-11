$('.LeftCell').css('display','none');
$('.Framework tr').first().hide();
$('div.posthead').hide();
$('#comment_form').hide();
$('#blog_post_info_block').hide();
$('.FooterCell').hide();
$('#blog-comments-placeholder').hide();