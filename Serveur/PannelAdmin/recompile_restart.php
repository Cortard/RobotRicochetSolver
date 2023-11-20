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
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
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
                    $output =null;
                    $return_var = null;
                    $result = exec('/home/ricochet/buildServeur.sh', $output, $return_var);
                    echo "Result : <pre>$result</pre>";
                    echo "Output :";
                    var_dump($output);
                    echo "\n Return var : <pre>$return_var</pre>";
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
        <div class="headerLog">
            <div class="joliButton">Logs</div>
            <div class="joliButton" >Filters :</div>
            <?php
                $levels= ['DEBUG', 'VERBOSE', 'DETAILS', 'INFO', 'WARNING', 'ERROR'];
                $levelsColor = ['grey', 'green', 'blue', 'white', 'orange', 'red'];
                foreach ($levels as $level) {
                    echo '<div class="joliButton filterResult" >';
                    $checked = (! isset($_GET['LOG_LEVEL_' . $level]) || $_GET['LOG_LEVEL_' . $level]==1)?'checked':'';
                    echo '<input class="checkboxAdminPanel" type="checkbox" id="LOG_LEVEL_' . $level . '"  name="LOG_LEVEL_' . $level . '" onclick="onClickFilter(this)" ' . $checked . '>';
                    echo '<label for="LOG_LEVEL_' . $level . '" style="color: ' . $levelsColor[array_search($level, $levels)] . '">' . $level . '</label>';
                    echo '</div>';
                }
            ?>
        </div>
        <div class="result">
            <?php
                $path = '/home/ricochet/logs.txt';
                $file = file($path, FILE_IGNORE_NEW_LINES);
                $levels = Array( 0 => 'ERROR', 1 => 'WARNING', 2 => 'INFO', 3 => 'DETAILS', 4 => 'VERBOSE', 5 => 'DEBUG');
                $levelsColor = Array( 0 => 'red', 1 => 'orange', 2 => 'white', 3 => 'blue', 4 => 'green', 5 => 'grey');
                $marge=30;
                foreach ($file as $line) {
                    $level = substr($line, strlen($line)-1, 1);
                    echo '<div class="resultPart ' . (isset($_GET['LOG_LEVEL_' . $levels[$level]]) && $_GET['LOG_LEVEL_' . $levels[$level]]==1?'':'resultIgnore') . '">';
                    echo '<p style="color: ' . $levelsColor[$level] . '; margin-left:' . ($level>3?($level-3)*$marge+50:($level==1?$marge+50:50)) . 'px">' . substr($line, 0, strlen($line)-2) . '</p>';
                    echo '</div>';
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
        var filters = document.getElementsByClassName("filterResult");
        var i;

        if(link.id === "refresh") {
            link.href += "?scrollY=" + window.scrollY + "&autoRefresh=";
            link.href += document.getElementById("autoRefresh").checked?'1':'0';
            for (i = 0; i < filters.length; i++) {
                link.href += '&' + filters[i].children[0].id + '=' + (filters[i].children[0].checked?'1':'0');
            }
            return true;
        }

        if(!document.getElementById("autoRefresh").checked)
            link.href+= "&autoRefresh=0";
        for (i = 0; i < filters.length; i++) {
            link.href += '&' + filters[i].children[0].id + '=' + (filters[i].children[0].checked?'1':'0');
        }
        return true;
    }

    function reload(){
        if (document.getElementById("autoRefresh").checked) {
            var url = 'recompile_restart.php?autoRefresh=1&scrollY=' + window.scrollY;
            var filters = document.getElementsByClassName("filterResult");
            for (var i = 0; i < filters.length; i++) {
                url += '&' + filters[i].children[0].id + '=' + (filters[i].children[0].checked?'1':'0');
            }
            window.location=url;
        }
    }

    function onClickRefresh(checkBox){
        if(checkBox.checked)
            setTimeout(reload, 5000);
    }

    function onClickFilter(filter){
        var url = 'recompile_restart.php?autoRefresh='+ (document.getElementById("autoRefresh").checked?'1':'0') + '&scrollY=' + window.scrollY;
        var filters = document.getElementsByClassName("filterResult");
        for (var i = 0; i < filters.length; i++) {
            url += '&' + filters[i].children[0].id + '=' + (filters[i].children[0].checked?'1':'0');
        }
        window.location=url;
    }

    window.onload = function() {
        window.scrollTo(0, <?= $_GET['scrollY'] ?? 0 ?>);
        if(document.getElementById("autoRefresh").checked)
            setTimeout(reload, 5000);
    };
</script>
<script src='js/arrow.js'></script>
</html>