<?php
session_start();

if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    if (!isset($_POST['csrf_token']) || !hash_equals($_SESSION['csrf_token'], $_POST['csrf_token'])) {
        die("CSRF token invalid.");
    }

    $con = mysqli_connect("localhost", "root", "", "problema4php");
    if (!$con) {
        die("Conexiune esuata.");
    }

    $username = $_POST['username'] ?? '';
    $password = $_POST['password'] ?? '';

    $stmt = mysqli_prepare($con, "SELECT id, password, is_active FROM users WHERE username = ?");
    mysqli_stmt_bind_param($stmt, "s", $username);
    mysqli_stmt_execute($stmt);
    mysqli_stmt_bind_result($stmt, $id, $hashed_password, $active);
    mysqli_stmt_fetch($stmt);
    mysqli_stmt_close($stmt);

    if ($id && password_verify($password, $hashed_password)) {
        if (!$active) {
            die("Contul nu este activat.");
        }
        $_SESSION['user_id'] = $id;
        header("Location: dashboard.php");
        exit;
    } else {
        echo "Date incorecte.";
    }
}
?>
