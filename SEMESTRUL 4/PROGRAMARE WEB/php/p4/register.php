<?php
use PHPMailer\PHPMailer\PHPMailer;
use PHPMailer\PHPMailer\Exception;

require 'vendor/autoload.php';
require 'config.php';

session_start();

// CSRF
if (!isset($_POST['csrf_token']) || !hash_equals($_SESSION['csrf_token'], $_POST['csrf_token'])) {
    die("CSRF token invalid.");
}

$username = trim($_POST["username"]);
$password = $_POST["password"];
$email = filter_var($_POST["email"], FILTER_VALIDATE_EMAIL);

// (opțional) Validări dezactivate, dar le poți activa când dorești
/*
$pattern = '/^[a-zA-Z][a-zA-Z0-9-_\.]{1,30}$/';
$patternPass = '/^(?=.*\d)(?=.*[a-z])(?=.*[A-Z])(?!.*\s).{6,}$/';
if (!$email || !preg_match($pattern, $username) || !preg_match($patternPass, $password)) {
    die("Date invalide.");
}
*/

$con = mysqli_connect("localhost", "root", "", "problema4php");
if (!$con) {
    die('Conexiune eșuată: ' . mysqli_connect_error());
}

$stmt = mysqli_prepare($con, "SELECT COUNT(*) FROM users WHERE username = ? OR email = ?");
mysqli_stmt_bind_param($stmt, "ss", $username, $email);
mysqli_stmt_execute($stmt);
mysqli_stmt_bind_result($stmt, $count);
mysqli_stmt_fetch($stmt);
mysqli_stmt_close($stmt);

if ($count > 0) {
    die("Utilizatorul sau emailul există deja.");
}

$hashed_password = password_hash($password, PASSWORD_DEFAULT);
$activation_token = bin2hex(random_bytes(32));

$stmt = mysqli_prepare($con, "INSERT INTO users (username, password, email, activation_token, is_active) VALUES (?, ?, ?, ?, 0)");
mysqli_stmt_bind_param($stmt, "ssss", $username, $hashed_password, $email, $activation_token);
mysqli_stmt_execute($stmt);
mysqli_stmt_close($stmt);
$mail = new PHPMailer(true);
try {
    $mail->isSMTP();
    $mail->Host = 'smtp.gmail.com';
    $mail->SMTPAuth = true;
    $mail->Username = 'ancatodut12@gmail.com';
    $mail->Password = 'doly mdwe dgxk crym';
    $mail->SMTPSecure = 'tls';
    $mail->Port = 587;

    $mail->setFrom('ancatodut12@gmail.com', 'Site-ul Meu');
    $mail->addAddress($email, htmlspecialchars($username)); // protecție XSS
    $mail->isHTML(true);
    $mail->Subject = 'Activare cont';

    $link = "http://localhost/php/p4/activate.php?token=$activation_token";
    $mail->Body = "<h1>Bine ai venit, " . htmlspecialchars($username) . "!</h1><p>Click <a href='" . htmlspecialchars($link) . "'>aici</a> pentru a activa contul tău.</p>";

    $mail->send();
    echo "Contul a fost creat. Verifica emailul pentru activare.";
} catch (Exception $e) {
    echo "Eroare la trimiterea emailului: " . htmlspecialchars($mail->ErrorInfo);
}

mysqli_close($con);
?>
