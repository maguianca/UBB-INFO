<?php
use PHPMailer\PHPMailer\PHPMailer;
use PHPMailer\PHPMailer\Exception;

require 'vendor/autoload.php';

$con = mysqli_connect("localhost", "root", "", "problema4php");
if (!$con) {
    die('Could not connect: ' . mysqli_connect_error());
}

$username = $_POST["username"];
$password = $_POST["password"];
$email = $_POST["email"];

// Verificare pattern username și password
$pattern = '/^[a-zA-Z][a-zA-Z0-9-_\.]{1,30}$/';
$patternPass = '/^(?=.*\d)(?=.*[a-z])(?=.*[A-Z])(?!.*\s).*$/';

if (!preg_match($pattern, $username)) {
    echo file_get_contents("index.html");
    echo "Auuch username";
    exit;
}
if (!preg_match($patternPass, $password)) {
    echo file_get_contents("index.html");
    echo "Auuch password";
    exit;
}

// Verificare existență user
$sql = "SELECT COUNT(*) FROM users WHERE username = ? AND password = ?";
$stmt = mysqli_prepare($con, $sql);
mysqli_stmt_bind_param($stmt, "ss", $username, $password);
mysqli_stmt_execute($stmt);
mysqli_stmt_bind_result($stmt, $count);
mysqli_stmt_fetch($stmt);
mysqli_stmt_close($stmt);

if ($count > 0) {
    echo file_get_contents("index.html");
    echo "Username existent";
} else {
    // Trimitere email cu PHPMailer
    $mail = new PHPMailer(true);
    try {
        $mail->isSMTP();
        $mail->Host = 'smtp.gmail.com';
        $mail->SMTPAuth = true;
        $mail->Username = 'ancatodut12@gmail.com';        // <-- schimbă cu Gmail-ul tău
        $mail->Password = 'doly mdwe dgxk crym';           // <-- schimbă cu parola de aplicație Gmail
        $mail->SMTPSecure = 'tls';
        $mail->Port = 587;

        $mail->setFrom('ancatodut@gmail.com', 'Site-ul Meu'); // <-- schimbă după preferință
        $mail->addAddress($email, $username);

        $mail->isHTML(true);
        $mail->Subject = 'Cont creat cu succes';
        $mail->Body    = "<h1>Salut $username!</h1><p>Contul tau a fost înregistrat cu succes.</p>";

        $mail->send();
        echo "Contul a fost creat și emailul a fost trimis!";
    } catch (Exception $e) {
        echo "Emailul nu a putut fi trimis. Eroare: {$mail->ErrorInfo}";
    }
}

mysqli_close($con);
?>
