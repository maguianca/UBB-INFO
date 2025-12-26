<?php
$conn = new mysqli("localhost", "root", "", "catalog");

$sql = "SELECT s.nume AS student, m.denumire AS materie, n.nota
        FROM note n
        JOIN studenti s ON n.student_id = s.id
        JOIN materii m ON n.materie_id = m.id
        ORDER BY s.nume, m.denumire";

$rez = $conn->query($sql);
?>

<h2>Note studenti</h2>
<table border="1" cellpadding="5">
    <tr><th>Student</th><th>Materie</th><th>Nota</th></tr>
    <?php while ($row = $rez->fetch_assoc()): ?>
        <tr>
            <td><?= htmlspecialchars($row['student']) ?></td>
            <td><?= htmlspecialchars($row['materie']) ?></td>
            <td><?= number_format($row['nota'], 2) ?></td>
        </tr>
    <?php endwhile; ?>
</table>
