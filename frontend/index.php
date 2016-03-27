<?php
error_reporting(E_ERROR | E_PARSE);

define('MAX_FILE_SIZE', 2000000);
define('MAX_MINUTES', 15);

if (strtoupper(substr(PHP_OS, 0, 3)) === 'WIN') {
    define('CRYPTO_PATH', 'encryptor.exe');
} else {
    define('CRYPTO_PATH', 'backend/FileCryptoBackend');
}

define('KEY_DIR', 'keys');
define('ENCRYPTED_DIR', 'encrypted');

define('MODE_ENCRYPT', 1);
define('MODE_DECRYPT', 2);

$result = 'Select File';
$output = array();
    
if (isset($_FILES["file"]))
{

    $uploadOk = true;
    $mode_key = 0;
    
    // Check if image file is a actual image or fake image
    if(isset($_POST["submit"])) 
    {
        if ($_FILES["file"]["error"] || $_FILES["file"]["size"] > MAX_FILE_SIZE)
        {
            $result = "Sorry, your file is too large.";
            $uploadOk = false;
        }
        
        if ($uploadOk)
        {
            if (isset($_POST['mode']))
            {
                if ((int)$_POST['mode'] == MODE_ENCRYPT)
                {
                    $mode_key = MODE_ENCRYPT;
                }
                else if ((int)$_POST['mode'] == MODE_DECRYPT)
                {
                    $mode_key = MODE_DECRYPT;
                }
                else
                {
                    $result = 'Correct mode not found';
                    $uploadOk = false;
                }
            }
            else
            {
                $result = 'No mode given';
                $uploadOk = false;
            }

        }
        
        if (isset($_POST['key']) == false && $uploadOk)
        {
            $result = 'Missing password';
            $uploadOk = false;
        }
        
        if  ($uploadOk)
        {
            $ext = pathinfo($_FILES["file"]["name"], PATHINFO_EXTENSION);
            $key_fname = KEY_DIR . '/' . uniqid('key_');
            $out_fname = ENCRYPTED_DIR . '/' . uniqid('f_');
            if ($mode_key == MODE_ENCRYPT)
            {
                $out_fname .= '.' . $ext . ".enc";
            }
            
            $mode = ($mode_key == MODE_ENCRYPT) ? '-e' : '-d';
            
            $result = CRYPTO_PATH . ' -i ' . $_FILES["file"]["tmp_name"] . ' -o ' . $out_fname . ' -k ' . $key_fname . ' ' . $mode;
            if (file_put_contents($key_fname, $_POST['key']) <= 0)
            {
                $result = "Failed to write key file!";
                $uploadOk = false;
            }
            
            if ($uploadOk)
            {
                $ret_code = "";
                $res_str = exec($result, $output, $ret_code);
                
                if ($ret_code != 0)
                {
                    $result = "Error when running program!";
                    $output = array($res_str);
                }
                else
                {
                    $link = $_SERVER['HTTP_HOST'] . '/' . dirname($_SERVER['PHP_SELF']) .  '/' . $out_fname;
                    $result = 'Encrypted  Successfully. Link: <a href="http://' . $link . '" class="btn btn-success" download/>download here</a> Will be available for a least ' . MAX_MINUTES . ' minutes.';
                }
            }
            
            // let's delete all files that are older than 15 minutes
            
            $files = glob(ENCRYPTED_DIR."/*");
            $now = time();
            foreach ($files as $file)
            {
                if (is_file($file))
                {
                    if ($now - filemtime($file) >= MAX_MINUTES * 60)
                    {
                        unlink($file);
                    }
                }
            }       
            
            unlink($key_fname);
        }
        
    }
}


include 'index.html.php';

?>
