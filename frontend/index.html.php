<!DOCTYPE html>
<html>
<head>

<title>Simple Encryptor</title>
<link rel="stylesheet" href="bootstrap/css/bootstrap.min.css">
<link rel="stylesheet" href="bootstrap/css/bootstrap-theme.min.css">
<link rel="stylesheet" href="bootstrap/css/custom.css">

</head>

<body>

    <div class="container">
        <div style="text-align: center;">
            <h1>Password-Protect your files (< 2MB)</h1>
            <h2><?= $result ?></h2>
        </div>
        <form action="index.php" method="post" enctype="multipart/form-data">
            <input class="form-control" placeholder="File" type="file" name="file" id="file"><br/>
            <input type="password" placeholder="Password" class="form-control" name="key" id="key"></br>
            
            <select class="form-control" name="mode" id="mode">
              <option value="1">Encrypt</option>
              <option value="2">Decrypt</option>
            </select>
            <br/>
            <input class="form-control" class="log" type="submit" value="Upload File" name="submit">
        </form>
    </div>
    
    <div class="container log">
        <p class="lead"><?= implode("<br/>", $output); ?></p>
    </div><!-- /.container -->
    
    <footer class="footer">
      <div class="container">
        <p class="text-muted">By <a href="http://absodev.com">Absodev</a>. We can help you make great software.</p>
      </div>
    </footer>

</body>
</html>