#!/usr/bin/env python

import subprocess
import bisect

tags = {
        1: "󰑊",
        2: "󰑊",
        4: "󰑊",
        8: "󰑊",
        16: "󰑊",
        32: "󰑊",
}

keys = {
    1: "ampersand",
    2: "eacute",
    4: "quotedbl",
    8: "apostrophe",
    16: "parenleft",
    32: "minus",
}

def int_to_tab(num):
    index = len(existed_tags) - 1
    tab = []
    while num > 0:
        if num - existed_tags[index] >= 0:
            tab.append(existed_tags[index])
            num -= existed_tags[index]
        index -= 1
    return tab[::-1]

existed_tags = [1, 2, 4, 8, 16, 32]
tags_dump = subprocess.check_output("dwm-dump-monitor 1", shell=True).decode('utf-8').split('\n')[:-1]


selected_num = int(tags_dump[0])
occupied_num = int(tags_dump[1])
urgent_num = int(tags_dump[2])

selected_tags = int_to_tab(selected_num)
occupied_tags = int_to_tab(occupied_num)
urgent_tags = int_to_tab(urgent_num)


box = '(box :class "tag_class" :orientation "h" :spacing 10 :space-evenly "true" '

for i in tags:
    if i in urgent_tags:
        btn = '(button :class "urgent_tag" :onclick "dwm-msg run_command view ' + str(i) + '" "' + tags[i] + '")'
    elif i in selected_tags:
        btn = '(button :class "selected_tag" :onclick "dwm-msg run_command view ' + str(i) + '" "' + tags[i] + '")'
    elif i in occupied_tags:
        btn = '(button :class "occupied_tag" :onclick "dwm-msg run_command view ' + str(i) + '" "' + tags[i] + '")'
    else:
        btn = '(button :class "void_tag" :onclick "xdotool key super+' + keys[i] + '" "' + tags[i] + '")'
    box += btn

box += ')'

print(box)