;;; .dir-locals.el --- Configuration of cmake-ide    -*- lexical-binding: t; -*-

;; Copyright (C) 2020  Yong Zhou

;; Author: Yong Zhou <yong@ikp078>

((nil .
      ((cmake-ide-project-dir . "./")
       (cmake-ide-build-dir . "./build/")
       (helm-make-build-dir . "build")
       (helm-make-arguments . "-j7")
       (helm-ctest-dir . "./build/")
       )))
