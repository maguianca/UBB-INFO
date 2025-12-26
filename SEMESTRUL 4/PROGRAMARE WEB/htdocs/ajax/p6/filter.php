<?php
$databasePath = 'C:/Programare web/Tema6/componente';
$pdo = new PDO("sqlite:" . $databasePath);
$pdo->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);

$sql = "SELECT * FROM notebookuri WHERE 1=1";
$params = [];

foreach (['producator', 'procesor', 'memorie', 'hdd', 'video'] as $field) {
    if (!empty($_POST[$field])) {
        $sql .= " AND $field = :$field";
        $params[$field] = $_POST[$field];
    }
}

$stmt = $pdo->prepare($sql);
$stmt->execute($params);
$produse = $stmt->fetchAll(PDO::FETCH_ASSOC);

if (empty($produse)) {
    echo "No products.";
} else {
    echo "<ul>";
    foreach ($produse as $p) {
        echo "<li>{$p['producator']} | {$p['procesor']} | {$p['memorie']} GB RAM | {$p['hdd']} GB HDD | {$p['video']}</li>";
    }
    echo "</ul>";
}
?>
