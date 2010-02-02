<?php

function theme_imagelinkformatter_formatter_cache($element) {
  if (empty($element['#item']['fid'])) {
    return '';
  }
  $matches = array();
  preg_match('/(?P<presetname>\w+)_imagelinkformatter_(?P<linkfield>\w+)/', $element['#formatter'], $matches);
  $presetname = $matches['presetname'];
  $field_name = 'field_'.$matches['linkfield'];

  $item = $element['#item'];
  $item['data']['alt'] = isset($item['data']['alt']) ? $item['data']['alt'] : '';
  $item['data']['title'] = isset($item['data']['title']) ? $item['data']['title'] : NULL;

  $imagetag = theme('imagecache', $presetname, $item['filepath'], $item['data']['alt'], $item['data']['title']); 

  
  
  // Render items.
  $class = "imagelinkcache imagelinkcache-$presetname imagelinkcache-$style imagelinkcache-{$element['#formatter']}";
  $path = _imagelinkformatter_get_image($element,$field_name);
  if (!$path) return $imagetag; 
  else return l($imagetag, $path, array('attributes' => array('class' => $class), 'html' => TRUE));
}

function theme_imagelinkformatter_formatter_reg($element) {
  if (empty($element['#item']['fid'])) {
    return '';
  }
  preg_match('/imagelinkformatter_(?P<linkfield>\w+)/', $element['#formatter'], $matches);
  $field_name = 'field_'.$matches['linkfield'];

  $imagetag = theme('imagefield_formatter_image_plain', $element);
  $class = 'imagefield imagefield-nodelink imagefield-'. $element['#field_name'];
  $path = _imagelinkformatter_get_image($element,$field_name);

  if (!$path) return $imagetag; 
  else return l($imagetag, $path, array('attributes' => array('class' => $class), 'html' => TRUE));
}

function _imagelinkformatter_get_image($element, $field_name) {
  $node = $element['#node'];
  $delta = $element['#item']['#delta'];
  if (empty($delta)) $delta = 0;
  if (!isset($node->{$field_name}) && $node->nid) {
    $node = node_load($node->nid);
  }
  return $node->{$field_name}[$delta]['url'];
}