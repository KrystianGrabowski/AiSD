<?php

function longestSubstring($a, $b) {
    $aLen = strlen($a);
    $bLen = strlen($b);
    $left = array_fill(0, $bLen, 0);
    $right = array_fill(0, $bLen, 0);
    $i = 0;
    $j = 0;


    // Find positions of first substring chars
    while ($j < $bLen) {
        if ($a[$i] == $b[$j]) {
            $left[$j++] = $i; 
        }
        $i++;
    }

    // Find positions of last substring chars
    $i = $aLen - 1;
    $j = $bLen - 1;
    while ($j > -1) {
        if ($a[$i] == $b[$j]) {
            $right[$j--] = $i;
        }
        $i--;
    }

    // Result is either distance from last char of the first substring to the end of 
    // the string [length - last index of first substring ] or
    // distance from start to the first char of the last substring, [first index of last substring]
    // distance between $first[$i-1] to $last[$i] - 1 (index from 0). [between chars]
    $longestSequence =  max($aLen- $left[$bLen - 1] - 1, $right[0]);
    for ($k=1; $k<$bLen; $k++) {
        $longestSequence = max($longestSequence, $right[$k] - $left[$k-1] - 1);
    }
    return $longestSequence;
}

function main() {
    $string = readline();
    $subString = readline();
    echo longestSubstring($string, $subString);
}

main();
?>