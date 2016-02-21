<?php

defined('APPLICATION_ENV') || define('APPLICATION_ENV', (getenv('APPLICATION_ENV') ? getenv('APPLICATION_ENV') : 'production'));

if (APPLICATION_ENV !== 'production') {
    error_reporting(E_ALL);
    ini_set('display_errors', 1);
}

require('../inc/AssetManager.php');
require('../inc/App.php');

$app = new App('../data/uploads', 5);
