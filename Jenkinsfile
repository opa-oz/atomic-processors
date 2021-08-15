pipeline {
    environment {
        githubCredentials = 'jenkins-github'
        githubUrl = 'https://github.com/opa-oz/atomic-processors'
    }

    agent any

    stages {
        stage('Cloning repository') {
            steps {
                git branch: 'main', credentialsId: githubCredentials, url: githubUrl
            }
        }

        stage('Download libs') {
            steps {
                sh('wget -P ./incl "https://github.com/CLIUtils/CLI11/releases/download/v2.0.0/CLI11.hpp"')
                sh('wget -P ./incl "https://raw.githubusercontent.com/vincentlaucsb/csv-parser/master/single_include/csv.hpp"')
            }
        }

        stage('Build binary') {
            environment {
                CC = "clang"
                CXX = "clang++"
            }

            steps {
                cmakeBuild generator: 'Unix Makefiles',
                        cleanBuild: true,
                        buildDir: 'build',
                        buildType: 'release',
                        sourceDir: '.',
                        installation: 'MyOwnCMake',
                        steps: [
                            [args: 'all', envVars: 'DESTDIR=${WORKSPACE}/artifacts']
                        ]
            }
        }
    }
}