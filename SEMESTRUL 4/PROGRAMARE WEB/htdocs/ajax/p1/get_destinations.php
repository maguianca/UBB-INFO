<?php
header('Content-Type: application/json');

$routes = [
    ["Cluj", "Timisoara"],
    ["Cluj", "Bucuresti"],
    ["Bucuresti", "Iasi"],
    ["Bucuresti", "Constanta"],
    ["Iasi", "Oradea"]
];

$departure = isset($_GET['departure']) ? $_GET['departure'] : '';
$results = [];

foreach ($routes as $route) {
    if ($route[0] === $departure) {
        $results[] = $route[1];
    }
}

echo json_encode($results);
?>
