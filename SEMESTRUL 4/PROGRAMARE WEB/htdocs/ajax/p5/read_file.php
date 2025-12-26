<?php
$root = realpath(__DIR__);
$path = realpath($root . DIRECTORY_SEPARATOR . $_GET['path']);

if (strpos($path, $root) !== 0 || !is_file($path)) {
    http_response_code(403);
    exit("Acces interzis.");
}

echo file_get_contents($path);
