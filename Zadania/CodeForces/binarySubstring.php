<?php

function kirksFunction($binaryString) {
    // Keep track of zeros and ones in sequence
    $zeros = 0;
    $ones = 0;
    // Iteration starts at the end. If x = 1 then there are two cases.
    // LIS starts from 1, then x = 0 will not affect LIS length 
    // LIS doesn't starts from 1, then x = 0 will affect LIS length
    //
    // If LIS ends with 1 then iterating from back we change change 1 to 0.
    // Assume that LIS ends with 1, then the number of zeros after 1 is bigger or equal than the number of ones.
    // This means that similar LIS can be obtain from zeros.
    // If $ones > $zeros it means that we can change LIS containing ones to LIS containing zeros.
    for ($i = strlen($binaryString)-1; $i >= 0; $i--) {
        if ($binaryString[$i] == '0') {
            $zeros++;
        }
        else {
            $ones++;
            if ($ones > $zeros) {
                $binaryString[$i] = '0';
                $ones--;
            }
        }
    }
    return $binaryString;
}

function main() {
    $binaryString = readline();
    echo kirksFunction($binaryString);
}

main();
?>