<?php

class App
{

    private $uploadsFolder;

    /**
     * How long file will be stored in systems, in minutes
     * @var int
     */
    private $fileTimeToLive;

    private $uploadResultText = '';

    function __construct($uploadDir, $fileTimeToLive = 3)
    {
        require_once('../inc/Upload.php');

        $this->uploadsFolder = $uploadDir;

        $this->fileTimeToLive = $fileTimeToLive * 60;

        $this->removeOutdatedFiles();

        $this->catchUpload();

        $this->showPage();
    }

    private function showPage()
    {
        $app = $this;
        include_once('../views/index.php');
    }

    private function removeOutdatedFiles()
    {
        $files = scandir($this->uploadsFolder);

        $ignoredFileNames = [
            '.',
            '..'
        ];

        if (!empty($files)) {
            foreach ($files as $file) {
                if (!in_array($file, $ignoredFileNames)) {
                    $fileCreationTime = filemtime($this->uploadsFolder . '/' . $file);
                    if ((time() - $fileCreationTime) >= $this->fileTimeToLive) {
                        unlink($this->uploadsFolder . '/' . $file);
                    }
                }
            }
        }
    }

    public function getUploadResultText()
    {
        return $this->uploadResultText;
    }

    private function catchUpload()
    {
        if (!empty($_FILES['upload'])) {
            $upload = Upload::factory($this->uploadsFolder);
            $upload->file($_FILES['upload']);
            $results = $upload->upload();

            $output = shell_exec('../../backend/main');

            if ($output) {
                $this->uploadResultText = $output;
            }
        }
    }
}