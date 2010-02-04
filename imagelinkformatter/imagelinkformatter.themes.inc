<?php

function theme_imagelinkformatter_formatter_cache($element) {
  if (empty($element['#item']['fid'])) {
    return '';
  }
  $matches = array();
  preg_match('/(?P<presetname>\w+)_imagelinkformatter_(?P<linkfield>\w+)/', $element['#formatter'], $matches);
  $presetname = $matches['presetname'];
  $field_name = 'field_'.$matches['linkfield'];

  $v = _cckcombomeal_get_field($element,$field_name);
  
  $item = $element['#item'];
  
  $item['data']['alt'] = isset($item['data']['alt']) ? $item['data']['alt'] : '';
  $item['data']['title'] = isset($item['data']['title']) ? $item['data']['title'] : ($v['title']?$v['title']:NULL);

  $imagetag = theme('imagecache', $presetname, $item['filepath'], $item['data']['alt'], $item['data']['title']); 

  
  
  // Render items.
  $class = "imagelinkcache imagelinkcache-$presetname imagelinkcache-$style imagelinkcache-{$element['#formatter']}";
 
  if (!$v['url']) return $imagetag; 
  else return l($imagetag, $v['url'], array('attributes' => array('class' => $class), 'html' => TRUE));
}

function theme_imagelinkformatter_formatter_reg($element) {
  if (empty($element['#item']['fid'])) {
    return '';
  }
  preg_match('/imagelinkformatter_(?P<linkfield>\w+)/', $element['#formatter'], $matches);
  $field_name = 'field_'.$matches['linkfield'];
  $v = _cckcombomeal_get_field($element,$field_name);
  
  $item['data']['title'] = isset($item['data']['title']) ? $item['data']['title'] : ($v['title']?$v['title']:NULL);
  
  $imagetag = theme('imagefield_formatter_image_plain', $element);
  
  $class = 'imagefield imagefield-nodelink imagefield-'. $element['#field_name'];
  
  if (!$v['url']) return $imagetag; 
  else return l($imagetag, $v['url'], array('attributes' => array('class' => $class), 'html' => TRUE));
}
