<?php
session_start();
if(isset($_POST['name']) && isset($_POST['passwd'])){
    sleep(5);
    if($_POST['name'] == 'bienTentéMais' && $_POST['passwd'] == 'NousN\'avonsPasLaisséLeMDP'){
        $_SESSION['connected'] = true;
        header('Location: recompile_restart.php');
    }else{
        header('Location: error.php');
    }
}
?>
<html lang="fr">
<head>
    <link rel="stylesheet" type="text/css" href="style.css" />
    <title>LOGIN</title>
</head>
<body>
    <div class="center">
        <form method="POST" enctype="multipart/form-data" action="index.php" class="joliBox">
            <label>
                <input type="text" name="name" placeholder="name">
            </label>
            <label>
                <input type="password" name="passwd" placeholder="password">
            </label>
            <button type="submit" class="joliButton">LOGIN</button>
        </form>
    </div>
</body>
</html>
