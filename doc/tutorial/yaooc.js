function header() {
document.write('\
<div id="header" class="header">\
<h1><center>YAOOC</center></h1>\
<h4><center>Yet Another Object Oriented C</center></h4>\
</div>\
');
}
function menu() {
var menu_items = [
  ["preface","Preface"],
  ["hello_world","Hello World"],
  ["new_delete","New/Delete"],
  ["type_info","Type Info"],
  ["custom_class","Custom Class"],
  ["custom_type_info","Custom Class Type Info"],
  ["class_table_instance","Class Table and Instance"],
  ["streams","Input/Output Streams"],
  ["constructors","Constructors"],
  ["inheritance","Inheritance"],
  ["yaoocpp","YAOOC PreProcessor"],
  ["pointer_bag","Pointer Bag"],
  ["exceptions","Exceptions"],
  ["memory_layout","Memory Layout"],
  ["placement_new_delete","Placement New and Delete"],
  ["containers","Containers"],
  ["vector","Vector"],
  ["map","Map"],
];
document.write('\
<div id="menu">\
<ul id="menu_list">\
');
var n=menu_items.length;
var i;
for(i=0;i<n;i++) {
  var menu_item=menu_items[i];
	var num;
	if(i<9) {
		num=i+1;
		num='0'+num;
	} else {
		num=i+1;
	}
document.write('\
<li>\
<a href="' + menu_item[0] + '.html">' + num + '. ' + menu_item[1] + '</a>\
</li>\
');
}
document.write('\
</ul>\
</div>\
');
}
