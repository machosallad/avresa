import os
import subprocess
import json

def generate_version_class():
    try:
        # Run GitVersion and capture the output
        result = subprocess.run(['dotnet-gitversion', '/output', 'json'], capture_output=True, text=True, check=True)
        version_info = json.loads(result.stdout)

        # Extract version information
        major = version_info['Major']
        minor = version_info['Minor']
        patch = version_info['Patch']
        semver = version_info['FullSemVer']
        tag = version_info['PreReleaseTag']
        build_date = version_info['CommitDate']

        # Generate the Version class in C++ syntax
        version_class = f"""#ifndef VERSION_H
#define VERSION_H

class Version {{
public:
    static const char* major() {{ return "{major}"; }}
    static const char* minor() {{ return "{minor}"; }}
    static const char* patch() {{ return "{patch}"; }}
    static const char* semver() {{ return "{semver}"; }}
    static const char* tag() {{ return "{tag}"; }}
    static const char* date() {{ return "{build_date}"; }}
}};

#endif // VERSION_H
"""

        # Write the Version class to a file
        with open('include/version.h', 'w') as f:
            f.write(version_class)

    except subprocess.CalledProcessError as e:
        print(f"Error running GitVersion: {e}")
    except FileNotFoundError:
        print("GitVersion not found. Please ensure it is installed and in your PATH.")

# Hook the script into the build process
def before_build(env, platform):
    if not os.getenv('CI'):
        print("Generating version class for local build.")
        generate_version_class()
    else:
        print("Skipping version generation in CI environment.")

if __name__ == "__main__":
    generate_version_class()
else:
    Import("env")
    before_build(None, None)