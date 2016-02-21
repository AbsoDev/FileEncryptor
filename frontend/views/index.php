<html lang="en">
<head>
    <title>File uploader</title>
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" media="all" href="<?= AssetManager::getInstance()->getAsset('css/main.css'); ?>">
</head>
<body>
<div>
    <p>Select file to encrypt:</p>

    <?php echo $app->getUploadResultText(); ?>
    <form action="" method="POST" enctype="multipart/form-data">
        <input type="file" name="upload">
        <input type="submit" value="Upload">
    </form>
</div>
<script src="<?= AssetManager::getInstance()->getAsset('js/app.js'); ?>"></script>
</body>
</html>
