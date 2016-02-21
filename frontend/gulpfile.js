var gulp = require('gulp');
var rimraf = require('gulp-rimraf');
var less = require('gulp-less');
var path = require('path');
var minifyCss = require('gulp-minify-css');
var notify = require("gulp-notify");
var runSequence = require('run-sequence');
var concat = require('gulp-concat');
var RevAll = require('gulp-rev-all');

gulp.task('js', function () {
    return gulp.src(
        [
            './node_modules/jquery/dist/jquery.js',
            './vendor/blueimp/jquery-file-upload/js/vendor/jquery.ui.widget.js',
            './vendor/blueimp/jquery-file-upload/js/jquery.fileupload.js',
            './public/assets/js/app.js',
        ])
        .pipe(concat('app.js'))
        .pipe(gulp.dest('public/build/temp/js'));
});

gulp.task('rev', function () {
    var revAll = new RevAll();
    return gulp.src(['public/build/temp/**/*'])
        .pipe(revAll.revision())
        .pipe(gulp.dest('public/build'))
        .pipe(revAll.manifestFile())
        .pipe(gulp.dest('public/build'));
    ;
});

gulp.task('clear-temp', function () {
    return gulp.src('public/build/temp/*', {read: false})
        .pipe(rimraf({force: true}));
});

gulp.task('build', function (callback) {
    runSequence('clear', 'css', 'js', 'img', 'rev', 'clear-temp', callback);
});

gulp.task('clear', function () {
    return gulp.src('public/build/*', {read: false})
        .pipe(rimraf({force: true}));
});

gulp.task('img', function () {
    return gulp.src('./assets/img/**/*')
        .pipe(gulp.dest('public/build/temp/img'));
});

gulp.task('css', function () {
    return gulp.src('public/assets/less/main.less')

        // use less
        .pipe(less({
            // list of include paths to be used
            paths: [path.join(__dirname)]
        }))

        // minify css
        .pipe(minifyCss())


        // place css file in folder
        .pipe(gulp.dest('public/build/temp/css'))
        ;
});

gulp.task('watch', function () {
    gulp.watch('public/assets/img/*', ['build']);
    gulp.watch('public/assets/js/*', ['build']);
    gulp.watch('public/assets/less/*', ['build']);
});
