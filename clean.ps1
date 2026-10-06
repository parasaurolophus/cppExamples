if (Test-Path -Path .\docs) {

    Remove-Item .\docs -Recurse
}

if (Test-Path -Path unit_tests) {

    Remove-Item -Path unit_tests
}

Get-ChildItem -Path * -Include *.o -Recurse | Remove-Item