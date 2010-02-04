<?php

function theme_textnoderefformatter_formatter($element) {
  preg_match('/textnoderefformatter_(?P<textfield>\w+)/', $element['#formatter'], $matches);
  $field_name = 'field_'.$matches['textfield'];
  $v = _cckcombomeal_get_field($element,$field_name);

  $txt = ($allowed =_text_allowed_values($element)) ? $allowed : $element['#item']['safe'];
  if ($v['value']) return l($txt,$v);
  return $txt;
}
