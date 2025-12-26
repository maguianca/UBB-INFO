<?php
session_start();

$n_options = [2, 3, 5, 10];
$default_n = 3;

if ($_SERVER['REQUEST_METHOD'] === 'POST' && isset($_POST['n']) && in_array((int)$_POST['n'], $n_options)) {
    $_SESSION['n'] = (int)$_POST['n'];
} elseif (isset($_GET['n']) && in_array((int)$_GET['n'], $n_options)) {
    $_SESSION['n'] = (int)$_GET['n'];
}

$n = $_SESSION['n'] ?? $default_n;

$page = isset($_GET['page']) ? max(1, (int)$_GET['page']) : 1;
$offset = ($page - 1) * $n;

// CSRF token
if (!isset($_SESSION['csrf_token'])) {
    $_SESSION['csrf_token'] = bin2hex(random_bytes(32));
}
$csrf_token = $_SESSION['csrf_token'];


$conn = new mysqli("localhost", "root", "", "trenuri");
if ($conn->connect_error) {
    die("Eroare conexiune: " . $conn->connect_error);
}
$conn->set_charset("utf8");

$total_stmt = $conn->prepare("SELECT COUNT(*) FROM produse");
$total_stmt->execute();
$total_stmt->bind_result($total);
$total_stmt->fetch();
$total_stmt->close();
$total_pages = ceil($total / $n);

$stmt = $conn->prepare("SELECT * FROM produse LIMIT ?, ?");
$stmt->bind_param("ii", $offset, $n);
$stmt->execute();
$rezultat = $stmt->get_result();
?>

<!DOCTYPE html>
<html lang="ro">
<head>
    <meta charset="UTF-8">
    <title>Produse Makeup</title>
    <style>
        body { font-family: sans-serif; padding: 20px; background: #f9f9f9; }
        .produs { border-bottom: 1px solid #ccc; padding: 10px 0; }
        .paginare a { margin: 5px; text-decoration: none; font-weight: bold; }
    </style>
</head>
<body>

<h2>Catalog produse makeup</h2>

<form method="post" action="problema2.php">
    <label>Alegeti cate produse doriti sa vedeti pe pagina:</label>
    <select name="n">
        <?php foreach ($n_options as $opt): ?>
            <option value="<?= $opt ?>" <?= $opt == $n ? 'selected' : '' ?>><?= $opt ?></option>
        <?php endforeach; ?>
    </select>
    <input type="hidden" name="csrf_token" value="<?= htmlspecialchars($csrf_token) ?>">
    <input type="submit" value="Aplica">
</form>

<hr>

<?php while ($prod = $rezultat->fetch_assoc()): ?>
    <div class="produs">
        <h3><?= htmlspecialchars($prod['nume']) ?> - <?= number_format($prod['pret'], 2) ?> RON</h3>
        <p><?= nl2br(htmlspecialchars($prod['descriere'])) ?></p>
    </div>
<?php endwhile; ?>

<div class="paginare">
    <?php if ($page > 1): ?>
        <a href="?page=<?= $page - 1 ?>&n=<?= $n ?>">← Anterior</a>
    <?php endif; ?>

    <?php if ($page < $total_pages): ?>
        <a href="?page=<?= $page + 1 ?>&n=<?= $n ?>">Urmator →</a>
    <?php endif; ?>
</div>

</body>
</html>

<?php $conn->close(); ?>
