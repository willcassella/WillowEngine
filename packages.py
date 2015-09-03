import os
import urllib
import zipfile
import shutil
import platform

packageDir = "packages"
tempDir = os.path.join(packageDir, "temp")
zipDir = os.path.join(tempDir, "packages.zip")

# Check if we need to download packages
if not os.path.exists(packageDir):	
	
	# Create package directory, and temp download directory
	os.makedirs(packageDir)
	os.makedirs(tempDir)
	
	# Identify and download correct set of packages
	if True:# platform.system() == "Windows":
		print "Downloading Windows packages..."
		urllib.urlretrieve ("http://www.willcassella.net/WillowEngine/packages/windows.zip", zipDir)
	
	print "Extracting packages..."
	pak = zipfile.ZipFile(zipDir)
	pak.extractall(packageDir)
	pak.close()
	
	# Delete temp directory
	shutil.rmtree(tempDir)
	
print "Packages up to date"