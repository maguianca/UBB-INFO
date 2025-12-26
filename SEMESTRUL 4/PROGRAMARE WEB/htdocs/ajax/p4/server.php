<?php
header('Content-Type: application/json');

$data = $_POST;
$board = json_decode($data['board']);
$ai = $data['ai'];

function checkWin($b, $sym) {
    $lines = [
        // randuri
        [[0,0],[0,1],[0,2]],
        [[1,0],[1,1],[1,2]],
        [[2,0],[2,1],[2,2]],
        // coloane
        [[0,0],[1,0],[2,0]],
        [[0,1],[1,1],[2,1]],
        [[0,2],[1,2],[2,2]],
        // diagonale
        [[0,0],[1,1],[2,2]],
        [[0,2],[1,1],[2,0]]
    ];

    foreach ($lines as $line) {
        [$a, $b1, $c] = $line;
        if ($b[$a[0]][$a[1]] === $sym &&
            $b[$a[0]][$a[1]] === $b[$b1[0]][$b1[1]] &&
            $b[$a[0]][$a[1]] === $b[$c[0]][$c[1]]) {
            return true;
        }
    }
    return false;
}


$empty = [];
for ($i = 0; $i < 3; $i++) {
    for ($j = 0; $j < 3; $j++) {
        if ($board[$i][$j] === "") {
            $empty[] = [$i, $j];
        }
    }
}

if (!empty($empty)) {
    $choice = $empty[array_rand($empty)];
    $board[$choice[0]][$choice[1]] = $ai;
}

$response = [ 'board' => $board ];

if (checkWin($board, $ai)) {
    $response['status'] = 'AI won!';
} elseif (count($empty) === 1) {
    $response['status'] = 'Tie!';
}
sleep(2);
echo json_encode($response);
