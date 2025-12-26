<?php
$con = mysqli_connect("localhost", "root", "", "problema4php");
$token = $_GET['token'] ?? '';

$stmt = mysqli_prepare($con, "UPDATE users SET is_active = 1, activation_token = NULL WHERE activation_token = ?");
mysqli_stmt_bind_param($stmt, "s", $token);
mysqli_stmt_execute($stmt);

if (mysqli_stmt_affected_rows($stmt) > 0) {
    $link ="http://localhost/php/p4/index.php";
    echo "Cont activat cu succes! <a href=$link>Autentifica-te</a>";
} else {
    echo "Token invalid sau cont deja activat.";
}
mysqli_stmt_close($stmt);
mysqli_close($con);
?>
