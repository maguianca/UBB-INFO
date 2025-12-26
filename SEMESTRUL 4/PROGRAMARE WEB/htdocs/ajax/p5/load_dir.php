<?php
header('Content-Type: application/json');

$root = realpath(__DIR__); // radacina
$path = realpath($root . DIRECTORY_SEPARATOR . $_GET['path']);

if (strpos($path, $root) !== 0) {
    echo json_encode([]); // securitate
    exit;
}

$entries = array_diff(scandir($path), ['.', '..']);
$result = [];

foreach ($entries as $entry) {
    $full = $path . DIRECTORY_SEPARATOR . $entry;
    $result[] = [
        'name' => $entry,
        'path' => str_replace($root . DIRECTORY_SEPARATOR, '', $full),
        'type' => is_dir($full) ? 'dir' : 'file'
    ];
}

echo json_encode($result);
