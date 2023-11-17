<?php
session_start();
if(!isset($_SESSION['connected']) || ! $_SESSION['connected']) {
    sleep(5);
    header('Location: error.php');
}

require_once 'include/makeLink.php';

?>

<!DOCTYPE html>
<html lang="fr">
<head>
    <link rel="stylesheet" type="text/css" href="style.css">
    <title>Admin Panel</title>
</head>
<body>
<header id="headerAdminPanel">
    <h1 id="titreAdminPanel">Admin Panel</h1>
    <nav id="navAdminPanel">
        <ul>
            <li><?= makeLink(false, false,'refresh') ?></li>
            <li><?= makeLink(true, false,'recompile') ?></li>
            <li><?= makeLink(false, true,'restart') ?></li>
            <li><?= makeLink(true, true,'recompile&restart') ?></li>
            <li>
                <div class="joliButton" id="divCheckboxAdminPanel">
                    <input class="checkboxAdminPanel" type="checkbox" id="autoRefresh"  name="autoRefresh" onclick="onClickRefresh(this)" <?= (isset($_GET['autoRefresh']) && $_GET['autoRefresh']==1)?'checked':'' ?>>
                    <label for="autoRefresh">Auto Refresh</label>
                </div>
            </li>
            <li><a class="joliButton" href="error.php">Logout</a></li>
        </ul>
    </nav>
</header>

<main id="mainAdminPanel">
    <?php
        if(isset($_GET['recompile']) && $_GET['recompile'] == 1){
            echo '<div class="joliBox boxFullWidth">';
                echo makeLink(true, false,'recompile2');
                echo '<div class="result">';
                    echo "<pre>Recompiling...</pre>";
                    $output = shell_exec('/home/ricochet/buildServeur.sh');
                    echo "<pre>$output</pre>";
                echo '</div>';
            echo '</div>';
        }
    ?>

    <?php
        if(isset($_GET['restart']) && $_GET['restart'] == 1){
            echo '<div class="joliBox boxFullWidth">';
                echo makeLink(false, true,'restart2');
                echo '<div class="result">';
                    echo "<pre>Try restart ...</pre>";
                    $output = shell_exec('systemctl restart ricochet.service');
                    echo "<pre>$output</pre>";
                echo '</div>';
            echo '</div>';
        }
    ?>
    <div class="joliBox boxFullWidth">
        <p class="joliButton" style="width: 34px">Logs</p>
        <div class="result">
            <?php
                $path = '/home/ricochet/logs.txt';
                $file = file($path, FILE_IGNORE_NEW_LINES);
                foreach ($file as $line) {
                    echo '<div class="resultPart"><p>' . htmlspecialchars($line) . '</p></div>';
                }
            ?>
        </div>
    </div>
</main>

    <footer>
        <span id="top-arrow"></span>
    </footer>
</body>

<script>
    function onClickLink(link){
        if(link.id === "refresh") {
            link.href += "?scrollY=" + window.scrollY + "&autoRefresh=";
            link.href += document.getElementById("autoRefresh").checked?'1':'0';
            return true;
        }

        if(!document.getElementById("autoRefresh").checked)
            link.href+= "&autoRefresh=0";

        return true;
    }

    function reload(){
        if (document.getElementById("autoRefresh").checked)
            window.location.href= 'recompile_restart.php?autoRefresh=1&scrollY=' + window.scrollY;
    }

    function onClickRefresh(checkBox){
        if(checkBox.checked)
            setTimeout(reload, 5000);
    }

    window.onload = function() {
        window.scrollTo(0, <?= $_GET['scrollY'] ?? 0 ?>);
        if(document.getElementById("autoRefresh").checked)
            setTimeout(reload, 5000);
    };
</script>
<script src='js/arrow.js'></script>
</html>