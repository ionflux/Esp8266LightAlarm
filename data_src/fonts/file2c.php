<?

$files = array(
'semantic.css',
'semantic.js',
'semantic.min.css',
'semantic.min.js',
);

$files = array_filter(scandir('./'), function($v){

switch(pathinfo($v, PATHINFO_EXTENSION)) {
case 'css':
case 'htm':
case 'html':
case 'js':
case 'eot':
case 'svg':
case 'ttf':
case 'woff':
return true;
}

return false;
});

$oldsize = 0;
$newsize = 0;

foreach ( $files as $file ) {

if (file_exists($file)) {
	
print "Compressing: " . $file . "\n";

  $data = file_get_contents( $file );

  $oldsize += strlen($data);

  $data = gzencode( $data, 9 );

  $newsize += strlen($data);

  file_put_contents($file . ".gz", $data );
}
}

print "Was: ". $oldsize . " bytes, now: " . $newsize . " bytes. Ratio: " . round( $oldsize / $newsize, 2 ) . ".";