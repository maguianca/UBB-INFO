<?php
session_start();
if (!isset($_SESSION['user_id'])) {
    header("Location: index.html");
    exit;
}
echo "Salut, esti autentificat! <a href='logout.php'>Logout</a>";
?>
