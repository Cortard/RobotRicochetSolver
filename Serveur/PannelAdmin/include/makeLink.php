<?php
function makeLink(bool $recompile, bool $restart, string $id) : string
{
    $link = '<a class="joliButton" href="recompile_restart.php';

    if($recompile){
        $link .= '?recompile=1';
    }
    if($restart){
        $link .= ($recompile?'&':'?').'restart=1';
    }
    $link .= '"';

    $link .= 'onclick="onClickLink(this)"';

    $link .= 'id="'.$id.'"';

    $link .= '>';

    if($recompile){
        $link .= 'Recompile';
        if($restart){
            $link .= ' & Restart';
        }
    } else if($restart){
        $link .= 'Restart';
    } else {
        $link .= 'Refresh';
    }

    $link .= '</a>';

    return $link;
}
