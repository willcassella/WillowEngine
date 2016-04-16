# Packages.py
import sys
import os
import zipfile
import shutil
import platform
import urllib.request

# Get package directory
packageUrl = sys.argv[1]
packageDir = "packages"
tempDir = os.path.join(packageDir, "temp")
zipDir = os.path.join(tempDir, "packages.zip")

# If package directory doesn't exist
if not os.path.exists(packageDir):	
	
    # Create package directory, and temp download directory
    os.makedirs(packageDir)
    os.makedirs(tempDir)
	
    # Dowload pacakges
    print("Downloading packages...")
    urllib.request.urlretrieve(packageUrl, zipDir)
	
    # Extract packages
    print("Extracting packages...")
    pak = zipfile.ZipFile(zipDir)
    pak.extractall(packageDir)
    pak.close()
	
    # Delete temp directory
    shutil.rmtree(tempDir)
	
print("Packages up to date")