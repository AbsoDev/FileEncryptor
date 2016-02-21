<?php

class AssetManager
{
    /**
     * @var AssetManager
     */
    protected static $instance;

    private $revManifest;

    function __construct()
    {
        $this->revManifest = json_decode(file_get_contents('build/rev-manifest.json'), true);
    }

    public static function getInstance()
    {
        if (null === self::$instance) {
            self::$instance = new AssetManager();
        }

        return self::$instance;
    }

    public function getAsset($asset)
    {
        return '/build/' . $this->revManifest[$asset];
    }

}