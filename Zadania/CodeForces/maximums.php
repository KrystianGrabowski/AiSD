<?php

function reverse($array) {
    $max = $array[0];
    for($i=1; $i<count($array); $i++) {
        $array[$i] = $array[$i] + $max;
        if ($array[$i] > $max) { $max = $array[$i]; } 
    }
    return $array;
}

function main() {
    $number = readline();
    $integers = readline();
    $intArray = array_map('intval', explode(' ', $integers));
    $intArray = reverse($intArray);
    foreach ($intArray as $elem) {
        echo $elem." ";
    }
}

main();
?>