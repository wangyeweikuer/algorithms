$('div.header').hide();
$('div.shortcut').hide();
$('div.breadcrumb.article_dq').hide();
$('div.meta.singlemeta').hide();
$('#ckepop').hide();
$('div.entrycontent div').hide();
$('div.otherContent_01').hide();
$('div.postnavi').hide();
$('div.postcomment').hide();
$('#cproIframe1holder').hide();
$('div.footer').hide();
$('div.sidebar').hide();
$('#cproIframe2holder').hide();
$('a[name=source]').parent().hide();
