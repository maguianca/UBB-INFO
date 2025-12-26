<?php
session_start();
$conn = new mysqli("localhost", "root", "", "comentarii_app");

if (!isset($_SESSION['csrf_token'])) {
    $_SESSION['csrf_token'] = bin2hex(random_bytes(32));
}

$stmt = $conn->prepare("SELECT nume, mesaj, data_adaugare FROM comentarii WHERE aprobat = 1 ORDER BY data_adaugare DESC");
$stmt->execute();
$comentarii = $stmt->get_result();

if ($_SERVER["REQUEST_METHOD"] === "POST") {
    if (!isset($_POST['csrf_token']) || $_POST['csrf_token'] !== $_SESSION['csrf_token']) {
        die("<p style='color:red'>Token CSRF invalid.</p>");
    }

    $nume = trim($_POST['nume']);
    $mesaj = trim($_POST['mesaj']);

    if ($nume && $mesaj) {
        $stmt = $conn->prepare("INSERT INTO comentarii (nume, mesaj) VALUES (?, ?)");
        $stmt->bind_param("ss", $nume, $mesaj);
        $stmt->execute();
        echo "<p style='color:green'>Comentariul a fost trimis spre aprobare.</p>";
    } else {
        echo "<p style='color:red'>Completeaza toate campurile.</p>";
    }
}
?>

<h2>5 parfumuri seducătoare cu miros de plajă</h2>
<p>Daca ai mirosit vreodata un parfum care te-a transportat pe o plaja insorita, probabil ca stii cat de special este sentimentul. E vremea sa te reconectezi cu acele note subtile si misterioase, care evoca libertatea zilelor de vara.
   Prospetimea valurilor inspumate, briza sarata si usor taioasa, nisipul incalzit sub soare, adierile scurte, suieratoare… nimic nu se compara cu sentimentul pe care il trezeste in tine o zi de vara petrecuta pe plaja, fara nimic de facut. Notele parfumurilor inspirate de vara sunt de obicei fructate, tropicale, asezonate cu cocos, uneori chiar cu caramel. Insa in ultimii ani parfumierii si-au dorit sa depaseasca aceste tipare si sa adopte o abordare mai sofisticata pentru a surprinde esenta plajei. Acea supradoza de note tropicale nu mai este dorita, preferand in locul ei subtilitatea, cremozitatea si misterul, pentru a crea o senzatie memorabila, familiara si intima.
   Asadar, notele fructate sunt acum mai subtile si de obicei acompaniate de parfumul sofisticat al florilor albe. Notele marine, greu de descris, sunt si ele adaugate pentru a obtine o complexitate seducatoare.</p>
<h3>Comentarii:</h3>
<?php while ($c = $comentarii->fetch_assoc()): ?>
    <div>
        <strong><?= htmlspecialchars($c['nume']) ?></strong> (<?= $c['data_adaugare'] ?>)<br>
        <?= nl2br(htmlspecialchars($c['mesaj'])) ?>
        <hr>
    </div>
<?php endwhile; ?>

<h3>Adauga un comentariu</h3>
<form method="post">
    <input name="nume" placeholder="Numele tau" required><br>
    <textarea name="mesaj" placeholder="Comentariul tau" required></textarea><br>
    <input type="hidden" name="csrf_token" value="<?= htmlspecialchars($_SESSION['csrf_token']) ?>">
    <input type="submit" value="Trimite">
</form>
