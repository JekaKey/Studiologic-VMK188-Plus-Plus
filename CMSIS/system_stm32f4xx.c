


<!DOCTYPE html>
<html>
  <head prefix="og: http://ogp.me/ns# fb: http://ogp.me/ns/fb# githubog: http://ogp.me/ns/fb/githubog#">
    <meta charset='utf-8'>
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
        <title>Fatarminator/system_stm32f4xx.c at master · JekaKey/Fatarminator</title>
    <link rel="search" type="application/opensearchdescription+xml" href="/opensearch.xml" title="GitHub" />
    <link rel="fluid-icon" href="https://github.com/fluidicon.png" title="GitHub" />
    <link rel="apple-touch-icon" sizes="57x57" href="/apple-touch-icon-114.png" />
    <link rel="apple-touch-icon" sizes="114x114" href="/apple-touch-icon-114.png" />
    <link rel="apple-touch-icon" sizes="72x72" href="/apple-touch-icon-144.png" />
    <link rel="apple-touch-icon" sizes="144x144" href="/apple-touch-icon-144.png" />
    <link rel="logo" type="image/svg" href="https://github-media-downloads.s3.amazonaws.com/github-logo.svg" />
    <meta property="og:image" content="https://github.global.ssl.fastly.net/images/modules/logos_page/Octocat.png">
    <meta name="hostname" content="fe1.rs.github.com">
    <meta name="ruby" content="ruby 1.9.3p194-tcs-github-tcmalloc (2012-05-25, TCS patched 2012-05-27, GitHub v1.0.32) [x86_64-linux]">
    <link rel="assets" href="https://github.global.ssl.fastly.net/">
    <link rel="xhr-socket" href="/_sockets" />
    
    


    <meta name="msapplication-TileImage" content="/windows-tile.png" />
    <meta name="msapplication-TileColor" content="#ffffff" />
    <meta name="selected-link" value="repo_source" data-pjax-transient />
    <meta content="collector.githubapp.com" name="octolytics-host" /><meta content="github" name="octolytics-app-id" /><meta content="5207288" name="octolytics-actor-id" /><meta content="user811" name="octolytics-actor-login" /><meta content="b9eb4911c06093c7ae0ecec5acea660b238c226396e7bfca872aa5c3537e5a5a" name="octolytics-actor-hash" />

    
    
    <link rel="icon" type="image/x-icon" href="/favicon.ico" />

    <meta content="authenticity_token" name="csrf-param" />
<meta content="hVSKTmTssB/YffJSYgu8OJ3Wu0FtrdI7cAFyHNLG2Eg=" name="csrf-token" />

    <link href="https://github.global.ssl.fastly.net/assets/github-889a72ca42388054915c6d822b2ce3caefa3919f.css" media="all" rel="stylesheet" type="text/css" />
    <link href="https://github.global.ssl.fastly.net/assets/github2-0136a1f869936b01696e5070e05c98a7971d3f91.css" media="all" rel="stylesheet" type="text/css" />
    


      <script src="https://github.global.ssl.fastly.net/assets/frameworks-eae23340ab2a6ba722166712e699c87aaf60ad8f.js" type="text/javascript"></script>
      <script src="https://github.global.ssl.fastly.net/assets/github-8cb63515f9e110eb912537d3c00587721fdc5b07.js" type="text/javascript"></script>
      
      <meta http-equiv="x-pjax-version" content="f29e63f9aa1cf09897660226577af809">

        <link data-pjax-transient rel='permalink' href='/JekaKey/Fatarminator/blob/9b6119f756e051da4c930797186a1d3d9a1b82bd/system_stm32f4xx.c'>
  <meta property="og:title" content="Fatarminator"/>
  <meta property="og:type" content="githubog:gitrepository"/>
  <meta property="og:url" content="https://github.com/JekaKey/Fatarminator"/>
  <meta property="og:image" content="https://github.global.ssl.fastly.net/images/gravatars/gravatar-user-420.png"/>
  <meta property="og:site_name" content="GitHub"/>
  <meta property="og:description" content="Fatarminator - Fatar VMK188+ STM32 Project"/>

  <meta name="description" content="Fatarminator - Fatar VMK188+ STM32 Project" />

  <meta content="1628313" name="octolytics-dimension-user_id" /><meta content="JekaKey" name="octolytics-dimension-user_login" /><meta content="10221850" name="octolytics-dimension-repository_id" /><meta content="JekaKey/Fatarminator" name="octolytics-dimension-repository_nwo" /><meta content="true" name="octolytics-dimension-repository_public" /><meta content="false" name="octolytics-dimension-repository_is_fork" /><meta content="10221850" name="octolytics-dimension-repository_network_root_id" /><meta content="JekaKey/Fatarminator" name="octolytics-dimension-repository_network_root_nwo" />
  <link href="https://github.com/JekaKey/Fatarminator/commits/master.atom" rel="alternate" title="Recent Commits to Fatarminator:master" type="application/atom+xml" />

  </head>


  <body class="logged_in page-blob windows vis-public env-production ">

    <div class="wrapper">
      
      
      


      <div class="header header-logged-in true">
  <div class="container clearfix">

    <a class="header-logo-invertocat" href="https://github.com/">
  <span class="mega-octicon octicon-mark-github"></span>
</a>

    <div class="divider-vertical"></div>

      <a href="/notifications" class="notification-indicator tooltipped downwards" title="You have no unread notifications">
    <span class="mail-status all-read"></span>
  </a>
  <div class="divider-vertical"></div>


      <div class="command-bar js-command-bar  in-repository">
          <form accept-charset="UTF-8" action="/search" class="command-bar-form" id="top_search_form" method="get">

<input type="text" data-hotkey=" s" name="q" id="js-command-bar-field" placeholder="Search or type a command" tabindex="1" autocapitalize="off"
    
    data-username="user811"
      data-repo="JekaKey/Fatarminator"
      data-branch="master"
      data-sha="4a4aff2fd6d88413a42a9630c41a525e80188175"
  >

    <input type="hidden" name="nwo" value="JekaKey/Fatarminator" />

    <div class="select-menu js-menu-container js-select-menu search-context-select-menu">
      <span class="minibutton select-menu-button js-menu-target">
        <span class="js-select-button">This repository</span>
      </span>

      <div class="select-menu-modal-holder js-menu-content js-navigation-container">
        <div class="select-menu-modal">

          <div class="select-menu-item js-navigation-item js-this-repository-navigation-item selected">
            <span class="select-menu-item-icon octicon octicon-check"></span>
            <input type="radio" class="js-search-this-repository" name="search_target" value="repository" checked="checked" />
            <div class="select-menu-item-text js-select-button-text">This repository</div>
          </div> <!-- /.select-menu-item -->

          <div class="select-menu-item js-navigation-item js-all-repositories-navigation-item">
            <span class="select-menu-item-icon octicon octicon-check"></span>
            <input type="radio" name="search_target" value="global" />
            <div class="select-menu-item-text js-select-button-text">All repositories</div>
          </div> <!-- /.select-menu-item -->

        </div>
      </div>
    </div>

  <span class="octicon help tooltipped downwards" title="Show command bar help">
    <span class="octicon octicon-question"></span>
  </span>


  <input type="hidden" name="ref" value="cmdform">

</form>
        <ul class="top-nav">
            <li class="explore"><a href="/explore">Explore</a></li>
            <li><a href="https://gist.github.com">Gist</a></li>
            <li><a href="/blog">Blog</a></li>
          <li><a href="https://help.github.com">Help</a></li>
        </ul>
      </div>

    



    <ul id="user-links">
      <li>
        <a href="/user811" class="name">
          <img height="20" src="https://secure.gravatar.com/avatar/2af709af197f59a1f8a27e1bf28a56f2?s=140&amp;d=https://a248.e.akamai.net/assets.github.com%2Fimages%2Fgravatars%2Fgravatar-user-420.png" width="20" /> user811
        </a>
      </li>

        <li>
          <a href="/new" id="new_repo" class="tooltipped downwards" title="Create a new repo" aria-label="Create a new repo">
            <span class="octicon octicon-repo-create"></span>
          </a>
        </li>

        <li>
          <a href="/settings/profile" id="account_settings"
            class="tooltipped downwards"
            aria-label="Account settings "
            title="Account settings ">
            <span class="octicon octicon-tools"></span>
          </a>
        </li>
        <li>
          <a class="tooltipped downwards" href="/logout" data-method="post" id="logout" title="Sign out" aria-label="Sign out">
            <span class="octicon octicon-log-out"></span>
          </a>
        </li>

    </ul>

<div class="js-new-dropdown-contents hidden">
  

<ul class="dropdown-menu">
  <li>
    <a href="/new"><span class="octicon octicon-repo-create"></span> New repository</a>
  </li>
  <li>
    <a href="/organizations/new"><span class="octicon octicon-organization"></span> New organization</a>
  </li>



    <li class="section-title">
      <span title="JekaKey/Fatarminator">This repository</span>
    </li>
    <li>
      <a href="/JekaKey/Fatarminator/issues/new"><span class="octicon octicon-issue-opened"></span> New issue</a>
    </li>
</ul>

</div>


    
  </div>
</div>

      

      




          <div class="site" itemscope itemtype="http://schema.org/WebPage">
    
    <div class="pagehead repohead instapaper_ignore readability-menu">
      <div class="container">
        

<ul class="pagehead-actions">

    <li class="subscription">
      <form accept-charset="UTF-8" action="/notifications/subscribe" class="js-social-container" data-autosubmit="true" data-remote="true" method="post"><div style="margin:0;padding:0;display:inline"><input name="authenticity_token" type="hidden" value="hVSKTmTssB/YffJSYgu8OJ3Wu0FtrdI7cAFyHNLG2Eg=" /></div>  <input id="repository_id" name="repository_id" type="hidden" value="10221850" />

    <div class="select-menu js-menu-container js-select-menu">
        <a class="social-count js-social-count" href="/JekaKey/Fatarminator/watchers">
          3
        </a>
      <span class="minibutton select-menu-button with-count js-menu-target">
        <span class="js-select-button">
          <span class="octicon octicon-eye-unwatch"></span>
          Unwatch
        </span>
      </span>

      <div class="select-menu-modal-holder">
        <div class="select-menu-modal subscription-menu-modal js-menu-content">
          <div class="select-menu-header">
            <span class="select-menu-title">Notification status</span>
            <span class="octicon octicon-remove-close js-menu-close"></span>
          </div> <!-- /.select-menu-header -->

          <div class="select-menu-list js-navigation-container">

            <div class="select-menu-item js-navigation-item ">
              <span class="select-menu-item-icon octicon octicon-check"></span>
              <div class="select-menu-item-text">
                <input id="do_included" name="do" type="radio" value="included" />
                <h4>Not watching</h4>
                <span class="description">You only receive notifications for discussions in which you participate or are @mentioned.</span>
                <span class="js-select-button-text hidden-select-button-text">
                  <span class="octicon octicon-eye-watch"></span>
                  Watch
                </span>
              </div>
            </div> <!-- /.select-menu-item -->

            <div class="select-menu-item js-navigation-item selected">
              <span class="select-menu-item-icon octicon octicon octicon-check"></span>
              <div class="select-menu-item-text">
                <input checked="checked" id="do_subscribed" name="do" type="radio" value="subscribed" />
                <h4>Watching</h4>
                <span class="description">You receive notifications for all discussions in this repository.</span>
                <span class="js-select-button-text hidden-select-button-text">
                  <span class="octicon octicon-eye-unwatch"></span>
                  Unwatch
                </span>
              </div>
            </div> <!-- /.select-menu-item -->

            <div class="select-menu-item js-navigation-item ">
              <span class="select-menu-item-icon octicon octicon-check"></span>
              <div class="select-menu-item-text">
                <input id="do_ignore" name="do" type="radio" value="ignore" />
                <h4>Ignoring</h4>
                <span class="description">You do not receive any notifications for discussions in this repository.</span>
                <span class="js-select-button-text hidden-select-button-text">
                  <span class="octicon octicon-mute"></span>
                  Stop ignoring
                </span>
              </div>
            </div> <!-- /.select-menu-item -->

          </div> <!-- /.select-menu-list -->

        </div> <!-- /.select-menu-modal -->
      </div> <!-- /.select-menu-modal-holder -->
    </div> <!-- /.select-menu -->

</form>
    </li>

  <li>
  
<div class="js-toggler-container js-social-container starring-container ">
  <a href="/JekaKey/Fatarminator/unstar" class="minibutton with-count js-toggler-target star-button starred upwards" title="Unstar this repo" data-remote="true" data-method="post" rel="nofollow">
    <span class="octicon octicon-star-delete"></span><span class="text">Unstar</span>
  </a>
  <a href="/JekaKey/Fatarminator/star" class="minibutton with-count js-toggler-target star-button unstarred upwards" title="Star this repo" data-remote="true" data-method="post" rel="nofollow">
    <span class="octicon octicon-star"></span><span class="text">Star</span>
  </a>
  <a class="social-count js-social-count" href="/JekaKey/Fatarminator/stargazers">0</a>
</div>

  </li>


        <li>
          <a href="/JekaKey/Fatarminator/fork" class="minibutton with-count js-toggler-target fork-button lighter upwards" title="Fork this repo" rel="nofollow" data-method="post">
            <span class="octicon octicon-git-branch-create"></span><span class="text">Fork</span>
          </a>
          <a href="/JekaKey/Fatarminator/network" class="social-count">0</a>
        </li>


</ul>

        <h1 itemscope itemtype="http://data-vocabulary.org/Breadcrumb" class="entry-title public">
          <span class="repo-label"><span>public</span></span>
          <span class="mega-octicon octicon-repo"></span>
          <span class="author">
            <a href="/JekaKey" class="url fn" itemprop="url" rel="author"><span itemprop="title">JekaKey</span></a></span
          ><span class="repohead-name-divider">/</span><strong
          ><a href="/JekaKey/Fatarminator" class="js-current-repository js-repo-home-link">Fatarminator</a></strong>

          <span class="page-context-loader">
            <img alt="Octocat-spinner-32" height="16" src="https://github.global.ssl.fastly.net/images/spinners/octocat-spinner-32.gif" width="16" />
          </span>

        </h1>
      </div><!-- /.container -->
    </div><!-- /.repohead -->

    <div class="container">

      <div class="repository-with-sidebar repo-container ">

        <div class="repository-sidebar">
            

<div class="repo-nav repo-nav-full js-repository-container-pjax js-octicon-loaders">
  <div class="repo-nav-contents">
    <ul class="repo-menu">
      <li class="tooltipped leftwards" title="Code">
        <a href="/JekaKey/Fatarminator" aria-label="Code" class="js-selected-navigation-item selected" data-gotokey="c" data-pjax="true" data-selected-links="repo_source repo_downloads repo_commits repo_tags repo_branches /JekaKey/Fatarminator">
          <span class="octicon octicon-code"></span> <span class="full-word">Code</span>
          <img alt="Octocat-spinner-32" class="mini-loader" height="16" src="https://github.global.ssl.fastly.net/images/spinners/octocat-spinner-32.gif" width="16" />
</a>      </li>

        <li class="tooltipped leftwards" title="Issues">
          <a href="/JekaKey/Fatarminator/issues" aria-label="Issues" class="js-selected-navigation-item js-disable-pjax" data-gotokey="i" data-selected-links="repo_issues /JekaKey/Fatarminator/issues">
            <span class="octicon octicon-issue-opened"></span> <span class="full-word">Issues</span>
            <span class='counter'>0</span>
            <img alt="Octocat-spinner-32" class="mini-loader" height="16" src="https://github.global.ssl.fastly.net/images/spinners/octocat-spinner-32.gif" width="16" />
</a>        </li>

      <li class="tooltipped leftwards" title="Pull Requests"><a href="/JekaKey/Fatarminator/pulls" aria-label="Pull Requests" class="js-selected-navigation-item js-disable-pjax" data-gotokey="p" data-selected-links="repo_pulls /JekaKey/Fatarminator/pulls">
            <span class="octicon octicon-git-pull-request"></span> <span class="full-word">Pull Requests</span>
            <span class='counter'>0</span>
            <img alt="Octocat-spinner-32" class="mini-loader" height="16" src="https://github.global.ssl.fastly.net/images/spinners/octocat-spinner-32.gif" width="16" />
</a>      </li>


        <li class="tooltipped leftwards" title="Wiki">
          <a href="/JekaKey/Fatarminator/wiki" aria-label="Wiki" class="js-selected-navigation-item " data-pjax="true" data-selected-links="repo_wiki /JekaKey/Fatarminator/wiki">
            <span class="octicon octicon-book"></span> <span class="full-word">Wiki</span>
            <img alt="Octocat-spinner-32" class="mini-loader" height="16" src="https://github.global.ssl.fastly.net/images/spinners/octocat-spinner-32.gif" width="16" />
</a>        </li>
    </ul>
    <div class="repo-menu-separator"></div>
    <ul class="repo-menu">

      <li class="tooltipped leftwards" title="Pulse">
        <a href="/JekaKey/Fatarminator/pulse" aria-label="Pulse" class="js-selected-navigation-item " data-pjax="true" data-selected-links="pulse /JekaKey/Fatarminator/pulse">
          <span class="octicon octicon-pulse"></span> <span class="full-word">Pulse</span>
          <img alt="Octocat-spinner-32" class="mini-loader" height="16" src="https://github.global.ssl.fastly.net/images/spinners/octocat-spinner-32.gif" width="16" />
</a>      </li>

      <li class="tooltipped leftwards" title="Graphs">
        <a href="/JekaKey/Fatarminator/graphs" aria-label="Graphs" class="js-selected-navigation-item " data-pjax="true" data-selected-links="repo_graphs repo_contributors /JekaKey/Fatarminator/graphs">
          <span class="octicon octicon-graph"></span> <span class="full-word">Graphs</span>
          <img alt="Octocat-spinner-32" class="mini-loader" height="16" src="https://github.global.ssl.fastly.net/images/spinners/octocat-spinner-32.gif" width="16" />
</a>      </li>

      <li class="tooltipped leftwards" title="Network">
        <a href="/JekaKey/Fatarminator/network" aria-label="Network" class="js-selected-navigation-item js-disable-pjax" data-selected-links="repo_network /JekaKey/Fatarminator/network">
          <span class="octicon octicon-git-branch"></span> <span class="full-word">Network</span>
          <img alt="Octocat-spinner-32" class="mini-loader" height="16" src="https://github.global.ssl.fastly.net/images/spinners/octocat-spinner-32.gif" width="16" />
</a>      </li>

    </ul>

  </div>
</div>

            <div class="only-with-full-nav">
              

  

<div class="clone-url open"
  data-protocol-type="http"
  data-url="/users/set_protocol?protocol_selector=http&amp;protocol_type=push">
  <h3><strong>HTTPS</strong> clone URL</h3>

  <input type="text" class="clone js-url-field"
         value="https://github.com/JekaKey/Fatarminator.git" readonly="readonly">

  <span class="js-zeroclipboard url-box-clippy minibutton zeroclipboard-button" data-clipboard-text="https://github.com/JekaKey/Fatarminator.git" data-copied-hint="copied!" title="copy to clipboard"><span class="octicon octicon-clippy"></span></span>
</div>

  

<div class="clone-url "
  data-protocol-type="ssh"
  data-url="/users/set_protocol?protocol_selector=ssh&amp;protocol_type=push">
  <h3><strong>SSH</strong> clone URL</h3>

  <input type="text" class="clone js-url-field"
         value="git@github.com:JekaKey/Fatarminator.git" readonly="readonly">

  <span class="js-zeroclipboard url-box-clippy minibutton zeroclipboard-button" data-clipboard-text="git@github.com:JekaKey/Fatarminator.git" data-copied-hint="copied!" title="copy to clipboard"><span class="octicon octicon-clippy"></span></span>
</div>

  

<div class="clone-url "
  data-protocol-type="subversion"
  data-url="/users/set_protocol?protocol_selector=subversion&amp;protocol_type=push">
  <h3><strong>Subversion</strong> checkout URL</h3>

  <input type="text" class="clone js-url-field"
         value="https://github.com/JekaKey/Fatarminator" readonly="readonly">

  <span class="js-zeroclipboard url-box-clippy minibutton zeroclipboard-button" data-clipboard-text="https://github.com/JekaKey/Fatarminator" data-copied-hint="copied!" title="copy to clipboard"><span class="octicon octicon-clippy"></span></span>
</div>



<p class="clone-options">You can clone with
    <a href="#" class="js-clone-selector" data-protocol="http">HTTPS</a>,
    <a href="#" class="js-clone-selector" data-protocol="ssh">SSH</a>,
    <a href="#" class="js-clone-selector" data-protocol="subversion">Subversion</a>,
  and <a href="https://help.github.com/articles/which-remote-url-should-i-use">other methods.</a>
</p>


  <a href="github-windows://openRepo/https://github.com/JekaKey/Fatarminator" class="minibutton sidebar-button">
    <span class="octicon octicon-device-desktop"></span>
    Clone in Desktop
  </a>

                <a href="/JekaKey/Fatarminator/archive/master.zip"
                   class="minibutton sidebar-button"
                   title="Download this repository as a zip file"
                   rel="nofollow">
                  <span class="octicon octicon-cloud-download"></span>
                  Download ZIP
                </a>
            </div>
        </div><!-- /.repository-sidebar -->

        <div id="js-repo-pjax-container" class="repository-content context-loader-container" data-pjax-container>
          


<!-- blob contrib key: blob_contributors:v21:9513a5af01946ca762567b80a672ba1f -->
<!-- blob contrib frag key: views10/v8/blob_contributors:v21:9513a5af01946ca762567b80a672ba1f -->

<p title="This is a placeholder element" class="js-history-link-replace hidden"></p>

<a href="/JekaKey/Fatarminator/find/master" data-pjax data-hotkey="t" style="display:none">Show File Finder</a>

<div class="file-navigation">
  


<div class="select-menu js-menu-container js-select-menu" >
  <span class="minibutton select-menu-button js-menu-target" data-hotkey="w"
    data-master-branch="master"
    data-ref="master">
    <span class="octicon octicon-git-branch"></span>
    <i>branch:</i>
    <span class="js-select-button">master</span>
  </span>

  <div class="select-menu-modal-holder js-menu-content js-navigation-container" data-pjax>

    <div class="select-menu-modal">
      <div class="select-menu-header">
        <span class="select-menu-title">Switch branches/tags</span>
        <span class="octicon octicon-remove-close js-menu-close"></span>
      </div> <!-- /.select-menu-header -->

      <div class="select-menu-filters">
        <div class="select-menu-text-filter">
          <input type="text" id="context-commitish-filter-field" class="js-filterable-field js-navigation-enable" placeholder="Find or create a branch…">
        </div>
        <div class="select-menu-tabs">
          <ul>
            <li class="select-menu-tab">
              <a href="#" data-tab-filter="branches" class="js-select-menu-tab">Branches</a>
            </li>
            <li class="select-menu-tab">
              <a href="#" data-tab-filter="tags" class="js-select-menu-tab">Tags</a>
            </li>
          </ul>
        </div><!-- /.select-menu-tabs -->
      </div><!-- /.select-menu-filters -->

      <div class="select-menu-list select-menu-tab-bucket js-select-menu-tab-bucket" data-tab-filter="branches">

        <div data-filterable-for="context-commitish-filter-field" data-filterable-type="substring">


            <div class="select-menu-item js-navigation-item selected">
              <span class="select-menu-item-icon octicon octicon-check"></span>
              <a href="/JekaKey/Fatarminator/blob/master/system_stm32f4xx.c" class="js-navigation-open select-menu-item-text js-select-button-text css-truncate-target" data-name="master" data-skip-pjax="true" rel="nofollow" title="master">master</a>
            </div> <!-- /.select-menu-item -->
        </div>

          <form accept-charset="UTF-8" action="/JekaKey/Fatarminator/branches" class="js-create-branch select-menu-item select-menu-new-item-form js-navigation-item js-new-item-form" method="post"><div style="margin:0;padding:0;display:inline"><input name="authenticity_token" type="hidden" value="hVSKTmTssB/YffJSYgu8OJ3Wu0FtrdI7cAFyHNLG2Eg=" /></div>
            <span class="octicon octicon-git-branch-create select-menu-item-icon"></span>
            <div class="select-menu-item-text">
              <h4>Create branch: <span class="js-new-item-name"></span></h4>
              <span class="description">from ‘master’</span>
            </div>
            <input type="hidden" name="name" id="name" class="js-new-item-value">
            <input type="hidden" name="branch" id="branch" value="master" />
            <input type="hidden" name="path" id="branch" value="system_stm32f4xx.c" />
          </form> <!-- /.select-menu-item -->

      </div> <!-- /.select-menu-list -->

      <div class="select-menu-list select-menu-tab-bucket js-select-menu-tab-bucket" data-tab-filter="tags">
        <div data-filterable-for="context-commitish-filter-field" data-filterable-type="substring">


        </div>

        <div class="select-menu-no-results">Nothing to show</div>
      </div> <!-- /.select-menu-list -->

    </div> <!-- /.select-menu-modal -->
  </div> <!-- /.select-menu-modal-holder -->
</div> <!-- /.select-menu -->

  <div class="breadcrumb">
    <span class='repo-root js-repo-root'><span itemscope="" itemtype="http://data-vocabulary.org/Breadcrumb"><a href="/JekaKey/Fatarminator" data-branch="master" data-direction="back" data-pjax="true" itemscope="url"><span itemprop="title">Fatarminator</span></a></span></span><span class="separator"> / </span><strong class="final-path">system_stm32f4xx.c</strong> <span class="js-zeroclipboard minibutton zeroclipboard-button" data-clipboard-text="system_stm32f4xx.c" data-copied-hint="copied!" title="copy to clipboard"><span class="octicon octicon-clippy"></span></span>
  </div>
</div>


  <div class="commit commit-loader file-history-tease js-deferred-content" data-url="/JekaKey/Fatarminator/contributors/master/system_stm32f4xx.c">
    Fetching contributors…

    <div class="participation">
      <p class="loader-loading"><img alt="Octocat-spinner-32-eaf2f5" height="16" src="https://github.global.ssl.fastly.net/images/spinners/octocat-spinner-32-EAF2F5.gif" width="16" /></p>
      <p class="loader-error">Cannot retrieve contributors at this time</p>
    </div>
  </div>

<div id="files" class="bubble">
  <div class="file">
    <div class="meta">
      <div class="info">
        <span class="icon"><b class="octicon octicon-file-text"></b></span>
        <span class="mode" title="File Mode">executable file</span>
          <span>554 lines (483 sloc)</span>
        <span>21.17 kb</span>
      </div>
      <div class="actions">
        <div class="button-group">
                <a class="minibutton"
                   href="/JekaKey/Fatarminator/edit/master/system_stm32f4xx.c"
                   data-method="post" rel="nofollow" data-hotkey="e">Edit</a>
          <a href="/JekaKey/Fatarminator/raw/master/system_stm32f4xx.c" class="button minibutton " id="raw-url">Raw</a>
            <a href="/JekaKey/Fatarminator/blame/master/system_stm32f4xx.c" class="button minibutton ">Blame</a>
          <a href="/JekaKey/Fatarminator/commits/master/system_stm32f4xx.c" class="button minibutton " rel="nofollow">History</a>
        </div><!-- /.button-group -->
            <a class="minibutton danger empty-icon tooltipped downwards"
               href="/JekaKey/Fatarminator/delete/master/system_stm32f4xx.c"
               title="" data-method="post" rel="nofollow">
            Delete
          </a>
      </div><!-- /.actions -->

    </div>
        <div class="blob-wrapper data type-c js-blob-data">
      <table class="file-code file-diff">
        <tr class="file-code-line">
          <td class="blob-line-nums">
            <span id="L1" rel="#L1">1</span>
<span id="L2" rel="#L2">2</span>
<span id="L3" rel="#L3">3</span>
<span id="L4" rel="#L4">4</span>
<span id="L5" rel="#L5">5</span>
<span id="L6" rel="#L6">6</span>
<span id="L7" rel="#L7">7</span>
<span id="L8" rel="#L8">8</span>
<span id="L9" rel="#L9">9</span>
<span id="L10" rel="#L10">10</span>
<span id="L11" rel="#L11">11</span>
<span id="L12" rel="#L12">12</span>
<span id="L13" rel="#L13">13</span>
<span id="L14" rel="#L14">14</span>
<span id="L15" rel="#L15">15</span>
<span id="L16" rel="#L16">16</span>
<span id="L17" rel="#L17">17</span>
<span id="L18" rel="#L18">18</span>
<span id="L19" rel="#L19">19</span>
<span id="L20" rel="#L20">20</span>
<span id="L21" rel="#L21">21</span>
<span id="L22" rel="#L22">22</span>
<span id="L23" rel="#L23">23</span>
<span id="L24" rel="#L24">24</span>
<span id="L25" rel="#L25">25</span>
<span id="L26" rel="#L26">26</span>
<span id="L27" rel="#L27">27</span>
<span id="L28" rel="#L28">28</span>
<span id="L29" rel="#L29">29</span>
<span id="L30" rel="#L30">30</span>
<span id="L31" rel="#L31">31</span>
<span id="L32" rel="#L32">32</span>
<span id="L33" rel="#L33">33</span>
<span id="L34" rel="#L34">34</span>
<span id="L35" rel="#L35">35</span>
<span id="L36" rel="#L36">36</span>
<span id="L37" rel="#L37">37</span>
<span id="L38" rel="#L38">38</span>
<span id="L39" rel="#L39">39</span>
<span id="L40" rel="#L40">40</span>
<span id="L41" rel="#L41">41</span>
<span id="L42" rel="#L42">42</span>
<span id="L43" rel="#L43">43</span>
<span id="L44" rel="#L44">44</span>
<span id="L45" rel="#L45">45</span>
<span id="L46" rel="#L46">46</span>
<span id="L47" rel="#L47">47</span>
<span id="L48" rel="#L48">48</span>
<span id="L49" rel="#L49">49</span>
<span id="L50" rel="#L50">50</span>
<span id="L51" rel="#L51">51</span>
<span id="L52" rel="#L52">52</span>
<span id="L53" rel="#L53">53</span>
<span id="L54" rel="#L54">54</span>
<span id="L55" rel="#L55">55</span>
<span id="L56" rel="#L56">56</span>
<span id="L57" rel="#L57">57</span>
<span id="L58" rel="#L58">58</span>
<span id="L59" rel="#L59">59</span>
<span id="L60" rel="#L60">60</span>
<span id="L61" rel="#L61">61</span>
<span id="L62" rel="#L62">62</span>
<span id="L63" rel="#L63">63</span>
<span id="L64" rel="#L64">64</span>
<span id="L65" rel="#L65">65</span>
<span id="L66" rel="#L66">66</span>
<span id="L67" rel="#L67">67</span>
<span id="L68" rel="#L68">68</span>
<span id="L69" rel="#L69">69</span>
<span id="L70" rel="#L70">70</span>
<span id="L71" rel="#L71">71</span>
<span id="L72" rel="#L72">72</span>
<span id="L73" rel="#L73">73</span>
<span id="L74" rel="#L74">74</span>
<span id="L75" rel="#L75">75</span>
<span id="L76" rel="#L76">76</span>
<span id="L77" rel="#L77">77</span>
<span id="L78" rel="#L78">78</span>
<span id="L79" rel="#L79">79</span>
<span id="L80" rel="#L80">80</span>
<span id="L81" rel="#L81">81</span>
<span id="L82" rel="#L82">82</span>
<span id="L83" rel="#L83">83</span>
<span id="L84" rel="#L84">84</span>
<span id="L85" rel="#L85">85</span>
<span id="L86" rel="#L86">86</span>
<span id="L87" rel="#L87">87</span>
<span id="L88" rel="#L88">88</span>
<span id="L89" rel="#L89">89</span>
<span id="L90" rel="#L90">90</span>
<span id="L91" rel="#L91">91</span>
<span id="L92" rel="#L92">92</span>
<span id="L93" rel="#L93">93</span>
<span id="L94" rel="#L94">94</span>
<span id="L95" rel="#L95">95</span>
<span id="L96" rel="#L96">96</span>
<span id="L97" rel="#L97">97</span>
<span id="L98" rel="#L98">98</span>
<span id="L99" rel="#L99">99</span>
<span id="L100" rel="#L100">100</span>
<span id="L101" rel="#L101">101</span>
<span id="L102" rel="#L102">102</span>
<span id="L103" rel="#L103">103</span>
<span id="L104" rel="#L104">104</span>
<span id="L105" rel="#L105">105</span>
<span id="L106" rel="#L106">106</span>
<span id="L107" rel="#L107">107</span>
<span id="L108" rel="#L108">108</span>
<span id="L109" rel="#L109">109</span>
<span id="L110" rel="#L110">110</span>
<span id="L111" rel="#L111">111</span>
<span id="L112" rel="#L112">112</span>
<span id="L113" rel="#L113">113</span>
<span id="L114" rel="#L114">114</span>
<span id="L115" rel="#L115">115</span>
<span id="L116" rel="#L116">116</span>
<span id="L117" rel="#L117">117</span>
<span id="L118" rel="#L118">118</span>
<span id="L119" rel="#L119">119</span>
<span id="L120" rel="#L120">120</span>
<span id="L121" rel="#L121">121</span>
<span id="L122" rel="#L122">122</span>
<span id="L123" rel="#L123">123</span>
<span id="L124" rel="#L124">124</span>
<span id="L125" rel="#L125">125</span>
<span id="L126" rel="#L126">126</span>
<span id="L127" rel="#L127">127</span>
<span id="L128" rel="#L128">128</span>
<span id="L129" rel="#L129">129</span>
<span id="L130" rel="#L130">130</span>
<span id="L131" rel="#L131">131</span>
<span id="L132" rel="#L132">132</span>
<span id="L133" rel="#L133">133</span>
<span id="L134" rel="#L134">134</span>
<span id="L135" rel="#L135">135</span>
<span id="L136" rel="#L136">136</span>
<span id="L137" rel="#L137">137</span>
<span id="L138" rel="#L138">138</span>
<span id="L139" rel="#L139">139</span>
<span id="L140" rel="#L140">140</span>
<span id="L141" rel="#L141">141</span>
<span id="L142" rel="#L142">142</span>
<span id="L143" rel="#L143">143</span>
<span id="L144" rel="#L144">144</span>
<span id="L145" rel="#L145">145</span>
<span id="L146" rel="#L146">146</span>
<span id="L147" rel="#L147">147</span>
<span id="L148" rel="#L148">148</span>
<span id="L149" rel="#L149">149</span>
<span id="L150" rel="#L150">150</span>
<span id="L151" rel="#L151">151</span>
<span id="L152" rel="#L152">152</span>
<span id="L153" rel="#L153">153</span>
<span id="L154" rel="#L154">154</span>
<span id="L155" rel="#L155">155</span>
<span id="L156" rel="#L156">156</span>
<span id="L157" rel="#L157">157</span>
<span id="L158" rel="#L158">158</span>
<span id="L159" rel="#L159">159</span>
<span id="L160" rel="#L160">160</span>
<span id="L161" rel="#L161">161</span>
<span id="L162" rel="#L162">162</span>
<span id="L163" rel="#L163">163</span>
<span id="L164" rel="#L164">164</span>
<span id="L165" rel="#L165">165</span>
<span id="L166" rel="#L166">166</span>
<span id="L167" rel="#L167">167</span>
<span id="L168" rel="#L168">168</span>
<span id="L169" rel="#L169">169</span>
<span id="L170" rel="#L170">170</span>
<span id="L171" rel="#L171">171</span>
<span id="L172" rel="#L172">172</span>
<span id="L173" rel="#L173">173</span>
<span id="L174" rel="#L174">174</span>
<span id="L175" rel="#L175">175</span>
<span id="L176" rel="#L176">176</span>
<span id="L177" rel="#L177">177</span>
<span id="L178" rel="#L178">178</span>
<span id="L179" rel="#L179">179</span>
<span id="L180" rel="#L180">180</span>
<span id="L181" rel="#L181">181</span>
<span id="L182" rel="#L182">182</span>
<span id="L183" rel="#L183">183</span>
<span id="L184" rel="#L184">184</span>
<span id="L185" rel="#L185">185</span>
<span id="L186" rel="#L186">186</span>
<span id="L187" rel="#L187">187</span>
<span id="L188" rel="#L188">188</span>
<span id="L189" rel="#L189">189</span>
<span id="L190" rel="#L190">190</span>
<span id="L191" rel="#L191">191</span>
<span id="L192" rel="#L192">192</span>
<span id="L193" rel="#L193">193</span>
<span id="L194" rel="#L194">194</span>
<span id="L195" rel="#L195">195</span>
<span id="L196" rel="#L196">196</span>
<span id="L197" rel="#L197">197</span>
<span id="L198" rel="#L198">198</span>
<span id="L199" rel="#L199">199</span>
<span id="L200" rel="#L200">200</span>
<span id="L201" rel="#L201">201</span>
<span id="L202" rel="#L202">202</span>
<span id="L203" rel="#L203">203</span>
<span id="L204" rel="#L204">204</span>
<span id="L205" rel="#L205">205</span>
<span id="L206" rel="#L206">206</span>
<span id="L207" rel="#L207">207</span>
<span id="L208" rel="#L208">208</span>
<span id="L209" rel="#L209">209</span>
<span id="L210" rel="#L210">210</span>
<span id="L211" rel="#L211">211</span>
<span id="L212" rel="#L212">212</span>
<span id="L213" rel="#L213">213</span>
<span id="L214" rel="#L214">214</span>
<span id="L215" rel="#L215">215</span>
<span id="L216" rel="#L216">216</span>
<span id="L217" rel="#L217">217</span>
<span id="L218" rel="#L218">218</span>
<span id="L219" rel="#L219">219</span>
<span id="L220" rel="#L220">220</span>
<span id="L221" rel="#L221">221</span>
<span id="L222" rel="#L222">222</span>
<span id="L223" rel="#L223">223</span>
<span id="L224" rel="#L224">224</span>
<span id="L225" rel="#L225">225</span>
<span id="L226" rel="#L226">226</span>
<span id="L227" rel="#L227">227</span>
<span id="L228" rel="#L228">228</span>
<span id="L229" rel="#L229">229</span>
<span id="L230" rel="#L230">230</span>
<span id="L231" rel="#L231">231</span>
<span id="L232" rel="#L232">232</span>
<span id="L233" rel="#L233">233</span>
<span id="L234" rel="#L234">234</span>
<span id="L235" rel="#L235">235</span>
<span id="L236" rel="#L236">236</span>
<span id="L237" rel="#L237">237</span>
<span id="L238" rel="#L238">238</span>
<span id="L239" rel="#L239">239</span>
<span id="L240" rel="#L240">240</span>
<span id="L241" rel="#L241">241</span>
<span id="L242" rel="#L242">242</span>
<span id="L243" rel="#L243">243</span>
<span id="L244" rel="#L244">244</span>
<span id="L245" rel="#L245">245</span>
<span id="L246" rel="#L246">246</span>
<span id="L247" rel="#L247">247</span>
<span id="L248" rel="#L248">248</span>
<span id="L249" rel="#L249">249</span>
<span id="L250" rel="#L250">250</span>
<span id="L251" rel="#L251">251</span>
<span id="L252" rel="#L252">252</span>
<span id="L253" rel="#L253">253</span>
<span id="L254" rel="#L254">254</span>
<span id="L255" rel="#L255">255</span>
<span id="L256" rel="#L256">256</span>
<span id="L257" rel="#L257">257</span>
<span id="L258" rel="#L258">258</span>
<span id="L259" rel="#L259">259</span>
<span id="L260" rel="#L260">260</span>
<span id="L261" rel="#L261">261</span>
<span id="L262" rel="#L262">262</span>
<span id="L263" rel="#L263">263</span>
<span id="L264" rel="#L264">264</span>
<span id="L265" rel="#L265">265</span>
<span id="L266" rel="#L266">266</span>
<span id="L267" rel="#L267">267</span>
<span id="L268" rel="#L268">268</span>
<span id="L269" rel="#L269">269</span>
<span id="L270" rel="#L270">270</span>
<span id="L271" rel="#L271">271</span>
<span id="L272" rel="#L272">272</span>
<span id="L273" rel="#L273">273</span>
<span id="L274" rel="#L274">274</span>
<span id="L275" rel="#L275">275</span>
<span id="L276" rel="#L276">276</span>
<span id="L277" rel="#L277">277</span>
<span id="L278" rel="#L278">278</span>
<span id="L279" rel="#L279">279</span>
<span id="L280" rel="#L280">280</span>
<span id="L281" rel="#L281">281</span>
<span id="L282" rel="#L282">282</span>
<span id="L283" rel="#L283">283</span>
<span id="L284" rel="#L284">284</span>
<span id="L285" rel="#L285">285</span>
<span id="L286" rel="#L286">286</span>
<span id="L287" rel="#L287">287</span>
<span id="L288" rel="#L288">288</span>
<span id="L289" rel="#L289">289</span>
<span id="L290" rel="#L290">290</span>
<span id="L291" rel="#L291">291</span>
<span id="L292" rel="#L292">292</span>
<span id="L293" rel="#L293">293</span>
<span id="L294" rel="#L294">294</span>
<span id="L295" rel="#L295">295</span>
<span id="L296" rel="#L296">296</span>
<span id="L297" rel="#L297">297</span>
<span id="L298" rel="#L298">298</span>
<span id="L299" rel="#L299">299</span>
<span id="L300" rel="#L300">300</span>
<span id="L301" rel="#L301">301</span>
<span id="L302" rel="#L302">302</span>
<span id="L303" rel="#L303">303</span>
<span id="L304" rel="#L304">304</span>
<span id="L305" rel="#L305">305</span>
<span id="L306" rel="#L306">306</span>
<span id="L307" rel="#L307">307</span>
<span id="L308" rel="#L308">308</span>
<span id="L309" rel="#L309">309</span>
<span id="L310" rel="#L310">310</span>
<span id="L311" rel="#L311">311</span>
<span id="L312" rel="#L312">312</span>
<span id="L313" rel="#L313">313</span>
<span id="L314" rel="#L314">314</span>
<span id="L315" rel="#L315">315</span>
<span id="L316" rel="#L316">316</span>
<span id="L317" rel="#L317">317</span>
<span id="L318" rel="#L318">318</span>
<span id="L319" rel="#L319">319</span>
<span id="L320" rel="#L320">320</span>
<span id="L321" rel="#L321">321</span>
<span id="L322" rel="#L322">322</span>
<span id="L323" rel="#L323">323</span>
<span id="L324" rel="#L324">324</span>
<span id="L325" rel="#L325">325</span>
<span id="L326" rel="#L326">326</span>
<span id="L327" rel="#L327">327</span>
<span id="L328" rel="#L328">328</span>
<span id="L329" rel="#L329">329</span>
<span id="L330" rel="#L330">330</span>
<span id="L331" rel="#L331">331</span>
<span id="L332" rel="#L332">332</span>
<span id="L333" rel="#L333">333</span>
<span id="L334" rel="#L334">334</span>
<span id="L335" rel="#L335">335</span>
<span id="L336" rel="#L336">336</span>
<span id="L337" rel="#L337">337</span>
<span id="L338" rel="#L338">338</span>
<span id="L339" rel="#L339">339</span>
<span id="L340" rel="#L340">340</span>
<span id="L341" rel="#L341">341</span>
<span id="L342" rel="#L342">342</span>
<span id="L343" rel="#L343">343</span>
<span id="L344" rel="#L344">344</span>
<span id="L345" rel="#L345">345</span>
<span id="L346" rel="#L346">346</span>
<span id="L347" rel="#L347">347</span>
<span id="L348" rel="#L348">348</span>
<span id="L349" rel="#L349">349</span>
<span id="L350" rel="#L350">350</span>
<span id="L351" rel="#L351">351</span>
<span id="L352" rel="#L352">352</span>
<span id="L353" rel="#L353">353</span>
<span id="L354" rel="#L354">354</span>
<span id="L355" rel="#L355">355</span>
<span id="L356" rel="#L356">356</span>
<span id="L357" rel="#L357">357</span>
<span id="L358" rel="#L358">358</span>
<span id="L359" rel="#L359">359</span>
<span id="L360" rel="#L360">360</span>
<span id="L361" rel="#L361">361</span>
<span id="L362" rel="#L362">362</span>
<span id="L363" rel="#L363">363</span>
<span id="L364" rel="#L364">364</span>
<span id="L365" rel="#L365">365</span>
<span id="L366" rel="#L366">366</span>
<span id="L367" rel="#L367">367</span>
<span id="L368" rel="#L368">368</span>
<span id="L369" rel="#L369">369</span>
<span id="L370" rel="#L370">370</span>
<span id="L371" rel="#L371">371</span>
<span id="L372" rel="#L372">372</span>
<span id="L373" rel="#L373">373</span>
<span id="L374" rel="#L374">374</span>
<span id="L375" rel="#L375">375</span>
<span id="L376" rel="#L376">376</span>
<span id="L377" rel="#L377">377</span>
<span id="L378" rel="#L378">378</span>
<span id="L379" rel="#L379">379</span>
<span id="L380" rel="#L380">380</span>
<span id="L381" rel="#L381">381</span>
<span id="L382" rel="#L382">382</span>
<span id="L383" rel="#L383">383</span>
<span id="L384" rel="#L384">384</span>
<span id="L385" rel="#L385">385</span>
<span id="L386" rel="#L386">386</span>
<span id="L387" rel="#L387">387</span>
<span id="L388" rel="#L388">388</span>
<span id="L389" rel="#L389">389</span>
<span id="L390" rel="#L390">390</span>
<span id="L391" rel="#L391">391</span>
<span id="L392" rel="#L392">392</span>
<span id="L393" rel="#L393">393</span>
<span id="L394" rel="#L394">394</span>
<span id="L395" rel="#L395">395</span>
<span id="L396" rel="#L396">396</span>
<span id="L397" rel="#L397">397</span>
<span id="L398" rel="#L398">398</span>
<span id="L399" rel="#L399">399</span>
<span id="L400" rel="#L400">400</span>
<span id="L401" rel="#L401">401</span>
<span id="L402" rel="#L402">402</span>
<span id="L403" rel="#L403">403</span>
<span id="L404" rel="#L404">404</span>
<span id="L405" rel="#L405">405</span>
<span id="L406" rel="#L406">406</span>
<span id="L407" rel="#L407">407</span>
<span id="L408" rel="#L408">408</span>
<span id="L409" rel="#L409">409</span>
<span id="L410" rel="#L410">410</span>
<span id="L411" rel="#L411">411</span>
<span id="L412" rel="#L412">412</span>
<span id="L413" rel="#L413">413</span>
<span id="L414" rel="#L414">414</span>
<span id="L415" rel="#L415">415</span>
<span id="L416" rel="#L416">416</span>
<span id="L417" rel="#L417">417</span>
<span id="L418" rel="#L418">418</span>
<span id="L419" rel="#L419">419</span>
<span id="L420" rel="#L420">420</span>
<span id="L421" rel="#L421">421</span>
<span id="L422" rel="#L422">422</span>
<span id="L423" rel="#L423">423</span>
<span id="L424" rel="#L424">424</span>
<span id="L425" rel="#L425">425</span>
<span id="L426" rel="#L426">426</span>
<span id="L427" rel="#L427">427</span>
<span id="L428" rel="#L428">428</span>
<span id="L429" rel="#L429">429</span>
<span id="L430" rel="#L430">430</span>
<span id="L431" rel="#L431">431</span>
<span id="L432" rel="#L432">432</span>
<span id="L433" rel="#L433">433</span>
<span id="L434" rel="#L434">434</span>
<span id="L435" rel="#L435">435</span>
<span id="L436" rel="#L436">436</span>
<span id="L437" rel="#L437">437</span>
<span id="L438" rel="#L438">438</span>
<span id="L439" rel="#L439">439</span>
<span id="L440" rel="#L440">440</span>
<span id="L441" rel="#L441">441</span>
<span id="L442" rel="#L442">442</span>
<span id="L443" rel="#L443">443</span>
<span id="L444" rel="#L444">444</span>
<span id="L445" rel="#L445">445</span>
<span id="L446" rel="#L446">446</span>
<span id="L447" rel="#L447">447</span>
<span id="L448" rel="#L448">448</span>
<span id="L449" rel="#L449">449</span>
<span id="L450" rel="#L450">450</span>
<span id="L451" rel="#L451">451</span>
<span id="L452" rel="#L452">452</span>
<span id="L453" rel="#L453">453</span>
<span id="L454" rel="#L454">454</span>
<span id="L455" rel="#L455">455</span>
<span id="L456" rel="#L456">456</span>
<span id="L457" rel="#L457">457</span>
<span id="L458" rel="#L458">458</span>
<span id="L459" rel="#L459">459</span>
<span id="L460" rel="#L460">460</span>
<span id="L461" rel="#L461">461</span>
<span id="L462" rel="#L462">462</span>
<span id="L463" rel="#L463">463</span>
<span id="L464" rel="#L464">464</span>
<span id="L465" rel="#L465">465</span>
<span id="L466" rel="#L466">466</span>
<span id="L467" rel="#L467">467</span>
<span id="L468" rel="#L468">468</span>
<span id="L469" rel="#L469">469</span>
<span id="L470" rel="#L470">470</span>
<span id="L471" rel="#L471">471</span>
<span id="L472" rel="#L472">472</span>
<span id="L473" rel="#L473">473</span>
<span id="L474" rel="#L474">474</span>
<span id="L475" rel="#L475">475</span>
<span id="L476" rel="#L476">476</span>
<span id="L477" rel="#L477">477</span>
<span id="L478" rel="#L478">478</span>
<span id="L479" rel="#L479">479</span>
<span id="L480" rel="#L480">480</span>
<span id="L481" rel="#L481">481</span>
<span id="L482" rel="#L482">482</span>
<span id="L483" rel="#L483">483</span>
<span id="L484" rel="#L484">484</span>
<span id="L485" rel="#L485">485</span>
<span id="L486" rel="#L486">486</span>
<span id="L487" rel="#L487">487</span>
<span id="L488" rel="#L488">488</span>
<span id="L489" rel="#L489">489</span>
<span id="L490" rel="#L490">490</span>
<span id="L491" rel="#L491">491</span>
<span id="L492" rel="#L492">492</span>
<span id="L493" rel="#L493">493</span>
<span id="L494" rel="#L494">494</span>
<span id="L495" rel="#L495">495</span>
<span id="L496" rel="#L496">496</span>
<span id="L497" rel="#L497">497</span>
<span id="L498" rel="#L498">498</span>
<span id="L499" rel="#L499">499</span>
<span id="L500" rel="#L500">500</span>
<span id="L501" rel="#L501">501</span>
<span id="L502" rel="#L502">502</span>
<span id="L503" rel="#L503">503</span>
<span id="L504" rel="#L504">504</span>
<span id="L505" rel="#L505">505</span>
<span id="L506" rel="#L506">506</span>
<span id="L507" rel="#L507">507</span>
<span id="L508" rel="#L508">508</span>
<span id="L509" rel="#L509">509</span>
<span id="L510" rel="#L510">510</span>
<span id="L511" rel="#L511">511</span>
<span id="L512" rel="#L512">512</span>
<span id="L513" rel="#L513">513</span>
<span id="L514" rel="#L514">514</span>
<span id="L515" rel="#L515">515</span>
<span id="L516" rel="#L516">516</span>
<span id="L517" rel="#L517">517</span>
<span id="L518" rel="#L518">518</span>
<span id="L519" rel="#L519">519</span>
<span id="L520" rel="#L520">520</span>
<span id="L521" rel="#L521">521</span>
<span id="L522" rel="#L522">522</span>
<span id="L523" rel="#L523">523</span>
<span id="L524" rel="#L524">524</span>
<span id="L525" rel="#L525">525</span>
<span id="L526" rel="#L526">526</span>
<span id="L527" rel="#L527">527</span>
<span id="L528" rel="#L528">528</span>
<span id="L529" rel="#L529">529</span>
<span id="L530" rel="#L530">530</span>
<span id="L531" rel="#L531">531</span>
<span id="L532" rel="#L532">532</span>
<span id="L533" rel="#L533">533</span>
<span id="L534" rel="#L534">534</span>
<span id="L535" rel="#L535">535</span>
<span id="L536" rel="#L536">536</span>
<span id="L537" rel="#L537">537</span>
<span id="L538" rel="#L538">538</span>
<span id="L539" rel="#L539">539</span>
<span id="L540" rel="#L540">540</span>
<span id="L541" rel="#L541">541</span>
<span id="L542" rel="#L542">542</span>
<span id="L543" rel="#L543">543</span>
<span id="L544" rel="#L544">544</span>
<span id="L545" rel="#L545">545</span>
<span id="L546" rel="#L546">546</span>
<span id="L547" rel="#L547">547</span>
<span id="L548" rel="#L548">548</span>
<span id="L549" rel="#L549">549</span>
<span id="L550" rel="#L550">550</span>
<span id="L551" rel="#L551">551</span>
<span id="L552" rel="#L552">552</span>
<span id="L553" rel="#L553">553</span>

          </td>
          <td class="blob-line-code">
                  <div class="highlight"><pre><div class='line' id='LC1'><span class="cm">/**</span></div><div class='line' id='LC2'><span class="cm">  ******************************************************************************</span></div><div class='line' id='LC3'><span class="cm">  * @file    system_stm32f4xx.c</span></div><div class='line' id='LC4'><span class="cm">  * @author  MCD Application Team</span></div><div class='line' id='LC5'><span class="cm">  * @version V1.0.0</span></div><div class='line' id='LC6'><span class="cm">  * @date    30-September-2011</span></div><div class='line' id='LC7'><span class="cm">  * @brief   CMSIS Cortex-M4 Device Peripheral Access Layer System Source File.</span></div><div class='line' id='LC8'><span class="cm">  *          This file contains the system clock configuration for STM32F4xx devices,</span></div><div class='line' id='LC9'><span class="cm">  *          and is generated by the clock configuration tool</span></div><div class='line' id='LC10'><span class="cm">  *          stm32f4xx_Clock_Configuration_V1.0.0.xls</span></div><div class='line' id='LC11'><span class="cm">  *             </span></div><div class='line' id='LC12'><span class="cm">  * 1.  This file provides two functions and one global variable to be called from </span></div><div class='line' id='LC13'><span class="cm">  *     user application:</span></div><div class='line' id='LC14'><span class="cm">  *      - SystemInit(): Setups the system clock (System clock source, PLL Multiplier</span></div><div class='line' id='LC15'><span class="cm">  *                      and Divider factors, AHB/APBx prescalers and Flash settings),</span></div><div class='line' id='LC16'><span class="cm">  *                      depending on the configuration made in the clock xls tool. </span></div><div class='line' id='LC17'><span class="cm">  *                      This function is called at startup just after reset and </span></div><div class='line' id='LC18'><span class="cm">  *                      before branch to main program. This call is made inside</span></div><div class='line' id='LC19'><span class="cm">  *                      the &quot;startup_stm32f4xx.s&quot; file.</span></div><div class='line' id='LC20'><span class="cm">  *</span></div><div class='line' id='LC21'><span class="cm">  *      - SystemCoreClock variable: Contains the core clock (HCLK), it can be used</span></div><div class='line' id='LC22'><span class="cm">  *                                  by the user application to setup the SysTick </span></div><div class='line' id='LC23'><span class="cm">  *                                  timer or configure other parameters.</span></div><div class='line' id='LC24'><span class="cm">  *                                     </span></div><div class='line' id='LC25'><span class="cm">  *      - SystemCoreClockUpdate(): Updates the variable SystemCoreClock and must</span></div><div class='line' id='LC26'><span class="cm">  *                                 be called whenever the core clock is changed</span></div><div class='line' id='LC27'><span class="cm">  *                                 during program execution.</span></div><div class='line' id='LC28'><span class="cm">  *</span></div><div class='line' id='LC29'><span class="cm">  * 2. After each device reset the HSI (16 MHz) is used as system clock source.</span></div><div class='line' id='LC30'><span class="cm">  *    Then SystemInit() function is called, in &quot;startup_stm32f4xx.s&quot; file, to</span></div><div class='line' id='LC31'><span class="cm">  *    configure the system clock before to branch to main program.</span></div><div class='line' id='LC32'><span class="cm">  *</span></div><div class='line' id='LC33'><span class="cm">  * 3. If the system clock source selected by user fails to startup, the SystemInit()</span></div><div class='line' id='LC34'><span class="cm">  *    function will do nothing and HSI still used as system clock source. User can </span></div><div class='line' id='LC35'><span class="cm">  *    add some code to deal with this issue inside the SetSysClock() function.</span></div><div class='line' id='LC36'><span class="cm">  *</span></div><div class='line' id='LC37'><span class="cm">  * 4. The default value of HSE crystal is set to 8 MHz, refer to &quot;HSE_VALUE&quot; define</span></div><div class='line' id='LC38'><span class="cm">  *    in &quot;stm32f4xx.h&quot; file. When HSE is used as system clock source, directly or</span></div><div class='line' id='LC39'><span class="cm">  *    through PLL, and you are using different crystal you have to adapt the HSE</span></div><div class='line' id='LC40'><span class="cm">  *    value to your own configuration.</span></div><div class='line' id='LC41'><span class="cm">  *</span></div><div class='line' id='LC42'><span class="cm">  * 5. This file configures the system clock as follows:</span></div><div class='line' id='LC43'><span class="cm">  *=============================================================================</span></div><div class='line' id='LC44'><span class="cm">  *=============================================================================</span></div><div class='line' id='LC45'><span class="cm">  *        Supported STM32F4xx device revision    | Rev A</span></div><div class='line' id='LC46'><span class="cm">  *-----------------------------------------------------------------------------</span></div><div class='line' id='LC47'><span class="cm">  *        System Clock source                    | PLL (HSE)</span></div><div class='line' id='LC48'><span class="cm">  *-----------------------------------------------------------------------------</span></div><div class='line' id='LC49'><span class="cm">  *        SYSCLK(Hz)                             | 168000000</span></div><div class='line' id='LC50'><span class="cm">  *-----------------------------------------------------------------------------</span></div><div class='line' id='LC51'><span class="cm">  *        HCLK(Hz)                               | 168000000</span></div><div class='line' id='LC52'><span class="cm">  *-----------------------------------------------------------------------------</span></div><div class='line' id='LC53'><span class="cm">  *        AHB Prescaler                          | 1</span></div><div class='line' id='LC54'><span class="cm">  *-----------------------------------------------------------------------------</span></div><div class='line' id='LC55'><span class="cm">  *        APB1 Prescaler                         | 4</span></div><div class='line' id='LC56'><span class="cm">  *-----------------------------------------------------------------------------</span></div><div class='line' id='LC57'><span class="cm">  *        APB2 Prescaler                         | 2</span></div><div class='line' id='LC58'><span class="cm">  *-----------------------------------------------------------------------------</span></div><div class='line' id='LC59'><span class="cm">  *        HSE Frequency(Hz)                      | 8000000</span></div><div class='line' id='LC60'><span class="cm">  *-----------------------------------------------------------------------------</span></div><div class='line' id='LC61'><span class="cm">  *        PLL_M                                  | 8</span></div><div class='line' id='LC62'><span class="cm">  *-----------------------------------------------------------------------------</span></div><div class='line' id='LC63'><span class="cm">  *        PLL_N                                  | 336</span></div><div class='line' id='LC64'><span class="cm">  *-----------------------------------------------------------------------------</span></div><div class='line' id='LC65'><span class="cm">  *        PLL_P                                  | 2</span></div><div class='line' id='LC66'><span class="cm">  *-----------------------------------------------------------------------------</span></div><div class='line' id='LC67'><span class="cm">  *        PLL_Q                                  | 7</span></div><div class='line' id='LC68'><span class="cm">  *-----------------------------------------------------------------------------</span></div><div class='line' id='LC69'><span class="cm">  *        PLLI2S_N                               | NA</span></div><div class='line' id='LC70'><span class="cm">  *-----------------------------------------------------------------------------</span></div><div class='line' id='LC71'><span class="cm">  *        PLLI2S_R                               | NA</span></div><div class='line' id='LC72'><span class="cm">  *-----------------------------------------------------------------------------</span></div><div class='line' id='LC73'><span class="cm">  *        I2S input clock                        | NA</span></div><div class='line' id='LC74'><span class="cm">  *-----------------------------------------------------------------------------</span></div><div class='line' id='LC75'><span class="cm">  *        VDD(V)                                 | 3.3</span></div><div class='line' id='LC76'><span class="cm">  *-----------------------------------------------------------------------------</span></div><div class='line' id='LC77'><span class="cm">  *        Main regulator output voltage          | Scale1 mode</span></div><div class='line' id='LC78'><span class="cm">  *-----------------------------------------------------------------------------</span></div><div class='line' id='LC79'><span class="cm">  *        Flash Latency(WS)                      | 5</span></div><div class='line' id='LC80'><span class="cm">  *-----------------------------------------------------------------------------</span></div><div class='line' id='LC81'><span class="cm">  *        Prefetch Buffer                        | OFF</span></div><div class='line' id='LC82'><span class="cm">  *-----------------------------------------------------------------------------</span></div><div class='line' id='LC83'><span class="cm">  *        Instruction cache                      | ON</span></div><div class='line' id='LC84'><span class="cm">  *-----------------------------------------------------------------------------</span></div><div class='line' id='LC85'><span class="cm">  *        Data cache                             | ON</span></div><div class='line' id='LC86'><span class="cm">  *-----------------------------------------------------------------------------</span></div><div class='line' id='LC87'><span class="cm">  *        Require 48MHz for USB OTG FS,          | Enabled</span></div><div class='line' id='LC88'><span class="cm">  *        SDIO and RNG clock                     |</span></div><div class='line' id='LC89'><span class="cm">  *-----------------------------------------------------------------------------</span></div><div class='line' id='LC90'><span class="cm">  *=============================================================================</span></div><div class='line' id='LC91'><span class="cm">  ****************************************************************************** </span></div><div class='line' id='LC92'><span class="cm">  * @attention</span></div><div class='line' id='LC93'><span class="cm">  *</span></div><div class='line' id='LC94'><span class="cm">  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS</span></div><div class='line' id='LC95'><span class="cm">  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE</span></div><div class='line' id='LC96'><span class="cm">  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY</span></div><div class='line' id='LC97'><span class="cm">  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING</span></div><div class='line' id='LC98'><span class="cm">  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE</span></div><div class='line' id='LC99'><span class="cm">  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.</span></div><div class='line' id='LC100'><span class="cm">  *</span></div><div class='line' id='LC101'><span class="cm">  * &lt;h2&gt;&lt;center&gt;&amp;copy; COPYRIGHT 2011 STMicroelectronics&lt;/center&gt;&lt;/h2&gt;</span></div><div class='line' id='LC102'><span class="cm">  ******************************************************************************</span></div><div class='line' id='LC103'><span class="cm">  */</span></div><div class='line' id='LC104'><br/></div><div class='line' id='LC105'><span class="cm">/** @addtogroup CMSIS</span></div><div class='line' id='LC106'><span class="cm">  * @{</span></div><div class='line' id='LC107'><span class="cm">  */</span></div><div class='line' id='LC108'><br/></div><div class='line' id='LC109'><span class="cm">/** @addtogroup stm32f4xx_system</span></div><div class='line' id='LC110'><span class="cm">  * @{</span></div><div class='line' id='LC111'><span class="cm">  */</span>  </div><div class='line' id='LC112'>&nbsp;&nbsp;</div><div class='line' id='LC113'><span class="cm">/** @addtogroup STM32F4xx_System_Private_Includes</span></div><div class='line' id='LC114'><span class="cm">  * @{</span></div><div class='line' id='LC115'><span class="cm">  */</span></div><div class='line' id='LC116'><br/></div><div class='line' id='LC117'><span class="cp">#include &quot;stm32f4xx.h&quot;</span></div><div class='line' id='LC118'><br/></div><div class='line' id='LC119'><span class="cm">/**</span></div><div class='line' id='LC120'><span class="cm">  * @}</span></div><div class='line' id='LC121'><span class="cm">  */</span></div><div class='line' id='LC122'><br/></div><div class='line' id='LC123'><span class="cm">/** @addtogroup STM32F4xx_System_Private_TypesDefinitions</span></div><div class='line' id='LC124'><span class="cm">  * @{</span></div><div class='line' id='LC125'><span class="cm">  */</span></div><div class='line' id='LC126'><br/></div><div class='line' id='LC127'><span class="cm">/**</span></div><div class='line' id='LC128'><span class="cm">  * @}</span></div><div class='line' id='LC129'><span class="cm">  */</span></div><div class='line' id='LC130'><br/></div><div class='line' id='LC131'><span class="cm">/** @addtogroup STM32F4xx_System_Private_Defines</span></div><div class='line' id='LC132'><span class="cm">  * @{</span></div><div class='line' id='LC133'><span class="cm">  */</span></div><div class='line' id='LC134'><br/></div><div class='line' id='LC135'><span class="cm">/************************* Miscellaneous Configuration ************************/</span></div><div class='line' id='LC136'><span class="cm">/*!&lt; Uncomment the following line if you need to use external SRAM mounted</span></div><div class='line' id='LC137'><span class="cm">     on STM324xG_EVAL board as data memory  */</span></div><div class='line' id='LC138'><span class="cm">/* #define DATA_IN_ExtSRAM */</span></div><div class='line' id='LC139'><br/></div><div class='line' id='LC140'><span class="cm">/*!&lt; Uncomment the following line if you need to relocate your vector Table in</span></div><div class='line' id='LC141'><span class="cm">     Internal SRAM. */</span></div><div class='line' id='LC142'><span class="cm">/* #define VECT_TAB_SRAM */</span></div><div class='line' id='LC143'><span class="cp">#define VECT_TAB_OFFSET  0x00 </span><span class="cm">/*!&lt; Vector Table base offset field. </span></div><div class='line' id='LC144'><span class="cm">                                   This value must be a multiple of 0x200. */</span><span class="cp"></span></div><div class='line' id='LC145'><span class="cm">/******************************************************************************/</span></div><div class='line' id='LC146'><br/></div><div class='line' id='LC147'><span class="cm">/************************* PLL Parameters *************************************/</span></div><div class='line' id='LC148'><span class="cm">/* PLL_VCO = (HSE_VALUE or HSI_VALUE / PLL_M) * PLL_N */</span></div><div class='line' id='LC149'><span class="cp">#define PLL_M      8</span></div><div class='line' id='LC150'><span class="cp">#define PLL_N      336</span></div><div class='line' id='LC151'><br/></div><div class='line' id='LC152'><span class="cm">/* SYSCLK = PLL_VCO / PLL_P */</span></div><div class='line' id='LC153'><span class="cp">#define PLL_P      2</span></div><div class='line' id='LC154'><br/></div><div class='line' id='LC155'><span class="cm">/* USB OTG FS, SDIO and RNG Clock =  PLL_VCO / PLLQ */</span></div><div class='line' id='LC156'><span class="cp">#define PLL_Q      7</span></div><div class='line' id='LC157'><br/></div><div class='line' id='LC158'><span class="cm">/******************************************************************************/</span></div><div class='line' id='LC159'><br/></div><div class='line' id='LC160'><span class="cm">/**</span></div><div class='line' id='LC161'><span class="cm">  * @}</span></div><div class='line' id='LC162'><span class="cm">  */</span></div><div class='line' id='LC163'><br/></div><div class='line' id='LC164'><span class="cm">/** @addtogroup STM32F4xx_System_Private_Macros</span></div><div class='line' id='LC165'><span class="cm">  * @{</span></div><div class='line' id='LC166'><span class="cm">  */</span></div><div class='line' id='LC167'><br/></div><div class='line' id='LC168'><span class="cm">/**</span></div><div class='line' id='LC169'><span class="cm">  * @}</span></div><div class='line' id='LC170'><span class="cm">  */</span></div><div class='line' id='LC171'><br/></div><div class='line' id='LC172'><span class="cm">/** @addtogroup STM32F4xx_System_Private_Variables</span></div><div class='line' id='LC173'><span class="cm">  * @{</span></div><div class='line' id='LC174'><span class="cm">  */</span></div><div class='line' id='LC175'><br/></div><div class='line' id='LC176'>&nbsp;&nbsp;<span class="kt">uint32_t</span> <span class="n">SystemCoreClock</span> <span class="o">=</span> <span class="mi">168000000</span><span class="p">;</span></div><div class='line' id='LC177'><br/></div><div class='line' id='LC178'>&nbsp;&nbsp;<span class="n">__I</span> <span class="kt">uint8_t</span> <span class="n">AHBPrescTable</span><span class="p">[</span><span class="mi">16</span><span class="p">]</span> <span class="o">=</span> <span class="p">{</span><span class="mi">0</span><span class="p">,</span> <span class="mi">0</span><span class="p">,</span> <span class="mi">0</span><span class="p">,</span> <span class="mi">0</span><span class="p">,</span> <span class="mi">0</span><span class="p">,</span> <span class="mi">0</span><span class="p">,</span> <span class="mi">0</span><span class="p">,</span> <span class="mi">0</span><span class="p">,</span> <span class="mi">1</span><span class="p">,</span> <span class="mi">2</span><span class="p">,</span> <span class="mi">3</span><span class="p">,</span> <span class="mi">4</span><span class="p">,</span> <span class="mi">6</span><span class="p">,</span> <span class="mi">7</span><span class="p">,</span> <span class="mi">8</span><span class="p">,</span> <span class="mi">9</span><span class="p">};</span></div><div class='line' id='LC179'><br/></div><div class='line' id='LC180'><span class="cm">/**</span></div><div class='line' id='LC181'><span class="cm">  * @}</span></div><div class='line' id='LC182'><span class="cm">  */</span></div><div class='line' id='LC183'><br/></div><div class='line' id='LC184'><span class="cm">/** @addtogroup STM32F4xx_System_Private_FunctionPrototypes</span></div><div class='line' id='LC185'><span class="cm">  * @{</span></div><div class='line' id='LC186'><span class="cm">  */</span></div><div class='line' id='LC187'><br/></div><div class='line' id='LC188'><span class="k">static</span> <span class="kt">void</span> <span class="nf">SetSysClock</span><span class="p">(</span><span class="kt">void</span><span class="p">);</span></div><div class='line' id='LC189'><span class="cp">#ifdef DATA_IN_ExtSRAM</span></div><div class='line' id='LC190'>&nbsp;&nbsp;<span class="k">static</span> <span class="kt">void</span> <span class="nf">SystemInit_ExtMemCtl</span><span class="p">(</span><span class="kt">void</span><span class="p">);</span> </div><div class='line' id='LC191'><span class="cp">#endif </span><span class="cm">/* DATA_IN_ExtSRAM */</span><span class="cp"></span></div><div class='line' id='LC192'><br/></div><div class='line' id='LC193'><span class="cm">/**</span></div><div class='line' id='LC194'><span class="cm">  * @}</span></div><div class='line' id='LC195'><span class="cm">  */</span></div><div class='line' id='LC196'><br/></div><div class='line' id='LC197'><span class="cm">/** @addtogroup STM32F4xx_System_Private_Functions</span></div><div class='line' id='LC198'><span class="cm">  * @{</span></div><div class='line' id='LC199'><span class="cm">  */</span></div><div class='line' id='LC200'><br/></div><div class='line' id='LC201'><span class="cm">/**</span></div><div class='line' id='LC202'><span class="cm">  * @brief  Setup the microcontroller system</span></div><div class='line' id='LC203'><span class="cm">  *         Initialize the Embedded Flash Interface, the PLL and update the </span></div><div class='line' id='LC204'><span class="cm">  *         SystemFrequency variable.</span></div><div class='line' id='LC205'><span class="cm">  * @param  None</span></div><div class='line' id='LC206'><span class="cm">  * @retval None</span></div><div class='line' id='LC207'><span class="cm">  */</span></div><div class='line' id='LC208'><span class="kt">void</span> <span class="nf">SystemInit</span><span class="p">(</span><span class="kt">void</span><span class="p">)</span></div><div class='line' id='LC209'><span class="p">{</span></div><div class='line' id='LC210'>&nbsp;&nbsp;<span class="cm">/* FPU settings ------------------------------------------------------------*/</span></div><div class='line' id='LC211'>&nbsp;&nbsp;<span class="err">#</span><span class="k">if</span> <span class="p">(</span><span class="n">__FPU_PRESENT</span> <span class="o">==</span> <span class="mi">1</span><span class="p">)</span> <span class="o">&amp;&amp;</span> <span class="p">(</span><span class="n">__FPU_USED</span> <span class="o">==</span> <span class="mi">1</span><span class="p">)</span></div><div class='line' id='LC212'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">SCB</span><span class="o">-&gt;</span><span class="n">CPACR</span> <span class="o">|=</span> <span class="p">((</span><span class="mi">3UL</span> <span class="o">&lt;&lt;</span> <span class="mi">10</span><span class="o">*</span><span class="mi">2</span><span class="p">)</span><span class="o">|</span><span class="p">(</span><span class="mi">3UL</span> <span class="o">&lt;&lt;</span> <span class="mi">11</span><span class="o">*</span><span class="mi">2</span><span class="p">));</span>  <span class="cm">/* set CP10 and CP11 Full Access */</span></div><div class='line' id='LC213'>&nbsp;&nbsp;<span class="err">#</span><span class="n">endif</span></div><div class='line' id='LC214'><br/></div><div class='line' id='LC215'>&nbsp;&nbsp;<span class="cm">/* Reset the RCC clock configuration to the default reset state ------------*/</span></div><div class='line' id='LC216'>&nbsp;&nbsp;<span class="cm">/* Set HSION bit */</span></div><div class='line' id='LC217'>&nbsp;&nbsp;<span class="n">RCC</span><span class="o">-&gt;</span><span class="n">CR</span> <span class="o">|=</span> <span class="p">(</span><span class="kt">uint32_t</span><span class="p">)</span><span class="mh">0x00000001</span><span class="p">;</span></div><div class='line' id='LC218'><br/></div><div class='line' id='LC219'>&nbsp;&nbsp;<span class="cm">/* Reset CFGR register */</span></div><div class='line' id='LC220'>&nbsp;&nbsp;<span class="n">RCC</span><span class="o">-&gt;</span><span class="n">CFGR</span> <span class="o">=</span> <span class="mh">0x00000000</span><span class="p">;</span></div><div class='line' id='LC221'><br/></div><div class='line' id='LC222'>&nbsp;&nbsp;<span class="cm">/* Reset HSEON, CSSON and PLLON bits */</span></div><div class='line' id='LC223'>&nbsp;&nbsp;<span class="n">RCC</span><span class="o">-&gt;</span><span class="n">CR</span> <span class="o">&amp;=</span> <span class="p">(</span><span class="kt">uint32_t</span><span class="p">)</span><span class="mh">0xFEF6FFFF</span><span class="p">;</span></div><div class='line' id='LC224'><br/></div><div class='line' id='LC225'>&nbsp;&nbsp;<span class="cm">/* Reset PLLCFGR register */</span></div><div class='line' id='LC226'>&nbsp;&nbsp;<span class="n">RCC</span><span class="o">-&gt;</span><span class="n">PLLCFGR</span> <span class="o">=</span> <span class="mh">0x24003010</span><span class="p">;</span></div><div class='line' id='LC227'><br/></div><div class='line' id='LC228'>&nbsp;&nbsp;<span class="cm">/* Reset HSEBYP bit */</span></div><div class='line' id='LC229'>&nbsp;&nbsp;<span class="n">RCC</span><span class="o">-&gt;</span><span class="n">CR</span> <span class="o">&amp;=</span> <span class="p">(</span><span class="kt">uint32_t</span><span class="p">)</span><span class="mh">0xFFFBFFFF</span><span class="p">;</span></div><div class='line' id='LC230'><br/></div><div class='line' id='LC231'>&nbsp;&nbsp;<span class="cm">/* Disable all interrupts */</span></div><div class='line' id='LC232'>&nbsp;&nbsp;<span class="n">RCC</span><span class="o">-&gt;</span><span class="n">CIR</span> <span class="o">=</span> <span class="mh">0x00000000</span><span class="p">;</span></div><div class='line' id='LC233'><br/></div><div class='line' id='LC234'><span class="cp">#ifdef DATA_IN_ExtSRAM</span></div><div class='line' id='LC235'>&nbsp;&nbsp;<span class="n">SystemInit_ExtMemCtl</span><span class="p">();</span> </div><div class='line' id='LC236'><span class="cp">#endif </span><span class="cm">/* DATA_IN_ExtSRAM */</span><span class="cp"></span></div><div class='line' id='LC237'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</div><div class='line' id='LC238'>&nbsp;&nbsp;<span class="cm">/* Configure the System clock source, PLL Multiplier and Divider factors, </span></div><div class='line' id='LC239'><span class="cm">     AHB/APBx prescalers and Flash settings ----------------------------------*/</span></div><div class='line' id='LC240'>&nbsp;&nbsp;<span class="n">SetSysClock</span><span class="p">();</span></div><div class='line' id='LC241'><br/></div><div class='line' id='LC242'>&nbsp;&nbsp;<span class="cm">/* Configure the Vector Table location add offset address ------------------*/</span></div><div class='line' id='LC243'><span class="cp">#ifdef VECT_TAB_SRAM</span></div><div class='line' id='LC244'>&nbsp;&nbsp;<span class="n">SCB</span><span class="o">-&gt;</span><span class="n">VTOR</span> <span class="o">=</span> <span class="n">SRAM_BASE</span> <span class="o">|</span> <span class="n">VECT_TAB_OFFSET</span><span class="p">;</span> <span class="cm">/* Vector Table Relocation in Internal SRAM */</span></div><div class='line' id='LC245'><span class="cp">#else</span></div><div class='line' id='LC246'>&nbsp;&nbsp;<span class="n">SCB</span><span class="o">-&gt;</span><span class="n">VTOR</span> <span class="o">=</span> <span class="n">FLASH_BASE</span> <span class="o">|</span> <span class="n">VECT_TAB_OFFSET</span><span class="p">;</span> <span class="cm">/* Vector Table Relocation in Internal FLASH */</span></div><div class='line' id='LC247'><span class="cp">#endif</span></div><div class='line' id='LC248'><span class="p">}</span></div><div class='line' id='LC249'><br/></div><div class='line' id='LC250'><span class="cm">/**</span></div><div class='line' id='LC251'><span class="cm">   * @brief  Update SystemCoreClock variable according to Clock Register Values.</span></div><div class='line' id='LC252'><span class="cm">  *         The SystemCoreClock variable contains the core clock (HCLK), it can</span></div><div class='line' id='LC253'><span class="cm">  *         be used by the user application to setup the SysTick timer or configure</span></div><div class='line' id='LC254'><span class="cm">  *         other parameters.</span></div><div class='line' id='LC255'><span class="cm">  *           </span></div><div class='line' id='LC256'><span class="cm">  * @note   Each time the core clock (HCLK) changes, this function must be called</span></div><div class='line' id='LC257'><span class="cm">  *         to update SystemCoreClock variable value. Otherwise, any configuration</span></div><div class='line' id='LC258'><span class="cm">  *         based on this variable will be incorrect.         </span></div><div class='line' id='LC259'><span class="cm">  *     </span></div><div class='line' id='LC260'><span class="cm">  * @note   - The system frequency computed by this function is not the real </span></div><div class='line' id='LC261'><span class="cm">  *           frequency in the chip. It is calculated based on the predefined </span></div><div class='line' id='LC262'><span class="cm">  *           constant and the selected clock source:</span></div><div class='line' id='LC263'><span class="cm">  *             </span></div><div class='line' id='LC264'><span class="cm">  *           - If SYSCLK source is HSI, SystemCoreClock will contain the HSI_VALUE(*)</span></div><div class='line' id='LC265'><span class="cm">  *                                              </span></div><div class='line' id='LC266'><span class="cm">  *           - If SYSCLK source is HSE, SystemCoreClock will contain the HSE_VALUE(**)</span></div><div class='line' id='LC267'><span class="cm">  *                          </span></div><div class='line' id='LC268'><span class="cm">  *           - If SYSCLK source is PLL, SystemCoreClock will contain the HSE_VALUE(**) </span></div><div class='line' id='LC269'><span class="cm">  *             or HSI_VALUE(*) multiplied/divided by the PLL factors.</span></div><div class='line' id='LC270'><span class="cm">  *         </span></div><div class='line' id='LC271'><span class="cm">  *         (*) HSI_VALUE is a constant defined in stm32f4xx.h file (default value</span></div><div class='line' id='LC272'><span class="cm">  *             16 MHz) but the real value may vary depending on the variations</span></div><div class='line' id='LC273'><span class="cm">  *             in voltage and temperature.   </span></div><div class='line' id='LC274'><span class="cm">  *    </span></div><div class='line' id='LC275'><span class="cm">  *         (**) HSE_VALUE is a constant defined in stm32f4xx.h file (default value</span></div><div class='line' id='LC276'><span class="cm">  *              25 MHz), user has to ensure that HSE_VALUE is same as the real</span></div><div class='line' id='LC277'><span class="cm">  *              frequency of the crystal used. Otherwise, this function may</span></div><div class='line' id='LC278'><span class="cm">  *              have wrong result.</span></div><div class='line' id='LC279'><span class="cm">  *                </span></div><div class='line' id='LC280'><span class="cm">  *         - The result of this function could be not correct when using fractional</span></div><div class='line' id='LC281'><span class="cm">  *           value for HSE crystal.</span></div><div class='line' id='LC282'><span class="cm">  *     </span></div><div class='line' id='LC283'><span class="cm">  * @param  None</span></div><div class='line' id='LC284'><span class="cm">  * @retval None</span></div><div class='line' id='LC285'><span class="cm">  */</span></div><div class='line' id='LC286'><span class="kt">void</span> <span class="nf">SystemCoreClockUpdate</span><span class="p">(</span><span class="kt">void</span><span class="p">)</span></div><div class='line' id='LC287'><span class="p">{</span></div><div class='line' id='LC288'>&nbsp;&nbsp;<span class="kt">uint32_t</span> <span class="n">tmp</span> <span class="o">=</span> <span class="mi">0</span><span class="p">,</span> <span class="n">pllvco</span> <span class="o">=</span> <span class="mi">0</span><span class="p">,</span> <span class="n">pllp</span> <span class="o">=</span> <span class="mi">2</span><span class="p">,</span> <span class="n">pllsource</span> <span class="o">=</span> <span class="mi">0</span><span class="p">,</span> <span class="n">pllm</span> <span class="o">=</span> <span class="mi">2</span><span class="p">;</span></div><div class='line' id='LC289'>&nbsp;&nbsp;</div><div class='line' id='LC290'>&nbsp;&nbsp;<span class="cm">/* Get SYSCLK source -------------------------------------------------------*/</span></div><div class='line' id='LC291'>&nbsp;&nbsp;<span class="n">tmp</span> <span class="o">=</span> <span class="n">RCC</span><span class="o">-&gt;</span><span class="n">CFGR</span> <span class="o">&amp;</span> <span class="n">RCC_CFGR_SWS</span><span class="p">;</span></div><div class='line' id='LC292'><br/></div><div class='line' id='LC293'>&nbsp;&nbsp;<span class="k">switch</span> <span class="p">(</span><span class="n">tmp</span><span class="p">)</span></div><div class='line' id='LC294'>&nbsp;&nbsp;<span class="p">{</span></div><div class='line' id='LC295'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">case</span> <span class="mh">0x00</span>:  <span class="cm">/* HSI used as system clock source */</span></div><div class='line' id='LC296'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">SystemCoreClock</span> <span class="o">=</span> <span class="n">HSI_VALUE</span><span class="p">;</span></div><div class='line' id='LC297'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">break</span><span class="p">;</span></div><div class='line' id='LC298'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">case</span> <span class="mh">0x04</span>:  <span class="cm">/* HSE used as system clock source */</span></div><div class='line' id='LC299'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">SystemCoreClock</span> <span class="o">=</span> <span class="n">HSE_VALUE</span><span class="p">;</span></div><div class='line' id='LC300'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">break</span><span class="p">;</span></div><div class='line' id='LC301'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">case</span> <span class="mh">0x08</span>:  <span class="cm">/* PLL used as system clock source */</span></div><div class='line' id='LC302'><br/></div><div class='line' id='LC303'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="cm">/* PLL_VCO = (HSE_VALUE or HSI_VALUE / PLL_M) * PLL_N</span></div><div class='line' id='LC304'><span class="cm">         SYSCLK = PLL_VCO / PLL_P</span></div><div class='line' id='LC305'><span class="cm">         */</span>    </div><div class='line' id='LC306'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">pllsource</span> <span class="o">=</span> <span class="p">(</span><span class="n">RCC</span><span class="o">-&gt;</span><span class="n">PLLCFGR</span> <span class="o">&amp;</span> <span class="n">RCC_PLLCFGR_PLLSRC</span><span class="p">)</span> <span class="o">&gt;&gt;</span> <span class="mi">22</span><span class="p">;</span></div><div class='line' id='LC307'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">pllm</span> <span class="o">=</span> <span class="n">RCC</span><span class="o">-&gt;</span><span class="n">PLLCFGR</span> <span class="o">&amp;</span> <span class="n">RCC_PLLCFGR_PLLM</span><span class="p">;</span></div><div class='line' id='LC308'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</div><div class='line' id='LC309'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">if</span> <span class="p">(</span><span class="n">pllsource</span> <span class="o">!=</span> <span class="mi">0</span><span class="p">)</span></div><div class='line' id='LC310'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">{</span></div><div class='line' id='LC311'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="cm">/* HSE used as PLL clock source */</span></div><div class='line' id='LC312'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">pllvco</span> <span class="o">=</span> <span class="p">(</span><span class="n">HSE_VALUE</span> <span class="o">/</span> <span class="n">pllm</span><span class="p">)</span> <span class="o">*</span> <span class="p">((</span><span class="n">RCC</span><span class="o">-&gt;</span><span class="n">PLLCFGR</span> <span class="o">&amp;</span> <span class="n">RCC_PLLCFGR_PLLN</span><span class="p">)</span> <span class="o">&gt;&gt;</span> <span class="mi">6</span><span class="p">);</span></div><div class='line' id='LC313'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">}</span></div><div class='line' id='LC314'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">else</span></div><div class='line' id='LC315'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">{</span></div><div class='line' id='LC316'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="cm">/* HSI used as PLL clock source */</span></div><div class='line' id='LC317'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">pllvco</span> <span class="o">=</span> <span class="p">(</span><span class="n">HSI_VALUE</span> <span class="o">/</span> <span class="n">pllm</span><span class="p">)</span> <span class="o">*</span> <span class="p">((</span><span class="n">RCC</span><span class="o">-&gt;</span><span class="n">PLLCFGR</span> <span class="o">&amp;</span> <span class="n">RCC_PLLCFGR_PLLN</span><span class="p">)</span> <span class="o">&gt;&gt;</span> <span class="mi">6</span><span class="p">);</span>      </div><div class='line' id='LC318'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">}</span></div><div class='line' id='LC319'><br/></div><div class='line' id='LC320'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">pllp</span> <span class="o">=</span> <span class="p">(((</span><span class="n">RCC</span><span class="o">-&gt;</span><span class="n">PLLCFGR</span> <span class="o">&amp;</span> <span class="n">RCC_PLLCFGR_PLLP</span><span class="p">)</span> <span class="o">&gt;&gt;</span><span class="mi">16</span><span class="p">)</span> <span class="o">+</span> <span class="mi">1</span> <span class="p">)</span> <span class="o">*</span><span class="mi">2</span><span class="p">;</span></div><div class='line' id='LC321'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">SystemCoreClock</span> <span class="o">=</span> <span class="n">pllvco</span><span class="o">/</span><span class="n">pllp</span><span class="p">;</span></div><div class='line' id='LC322'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">break</span><span class="p">;</span></div><div class='line' id='LC323'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="nl">default:</span></div><div class='line' id='LC324'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">SystemCoreClock</span> <span class="o">=</span> <span class="n">HSI_VALUE</span><span class="p">;</span></div><div class='line' id='LC325'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">break</span><span class="p">;</span></div><div class='line' id='LC326'>&nbsp;&nbsp;<span class="p">}</span></div><div class='line' id='LC327'>&nbsp;&nbsp;<span class="cm">/* Compute HCLK frequency --------------------------------------------------*/</span></div><div class='line' id='LC328'>&nbsp;&nbsp;<span class="cm">/* Get HCLK prescaler */</span></div><div class='line' id='LC329'>&nbsp;&nbsp;<span class="n">tmp</span> <span class="o">=</span> <span class="n">AHBPrescTable</span><span class="p">[((</span><span class="n">RCC</span><span class="o">-&gt;</span><span class="n">CFGR</span> <span class="o">&amp;</span> <span class="n">RCC_CFGR_HPRE</span><span class="p">)</span> <span class="o">&gt;&gt;</span> <span class="mi">4</span><span class="p">)];</span></div><div class='line' id='LC330'>&nbsp;&nbsp;<span class="cm">/* HCLK frequency */</span></div><div class='line' id='LC331'>&nbsp;&nbsp;<span class="n">SystemCoreClock</span> <span class="o">&gt;&gt;=</span> <span class="n">tmp</span><span class="p">;</span></div><div class='line' id='LC332'><span class="p">}</span></div><div class='line' id='LC333'><br/></div><div class='line' id='LC334'><span class="cm">/**</span></div><div class='line' id='LC335'><span class="cm">  * @brief  Configures the System clock source, PLL Multiplier and Divider factors, </span></div><div class='line' id='LC336'><span class="cm">  *         AHB/APBx prescalers and Flash settings</span></div><div class='line' id='LC337'><span class="cm">  * @Note   This function should be called only once the RCC clock configuration  </span></div><div class='line' id='LC338'><span class="cm">  *         is reset to the default reset state (done in SystemInit() function).   </span></div><div class='line' id='LC339'><span class="cm">  * @param  None</span></div><div class='line' id='LC340'><span class="cm">  * @retval None</span></div><div class='line' id='LC341'><span class="cm">  */</span></div><div class='line' id='LC342'><span class="k">static</span> <span class="kt">void</span> <span class="nf">SetSysClock</span><span class="p">(</span><span class="kt">void</span><span class="p">)</span></div><div class='line' id='LC343'><span class="p">{</span></div><div class='line' id='LC344'><span class="cm">/******************************************************************************/</span></div><div class='line' id='LC345'><span class="cm">/*            PLL (clocked by HSE) used as System clock source                */</span></div><div class='line' id='LC346'><span class="cm">/******************************************************************************/</span></div><div class='line' id='LC347'>&nbsp;&nbsp;<span class="n">__IO</span> <span class="kt">uint32_t</span> <span class="n">StartUpCounter</span> <span class="o">=</span> <span class="mi">0</span><span class="p">,</span> <span class="n">HSEStatus</span> <span class="o">=</span> <span class="mi">0</span><span class="p">;</span></div><div class='line' id='LC348'>&nbsp;&nbsp;</div><div class='line' id='LC349'>&nbsp;&nbsp;<span class="cm">/* Enable HSE */</span></div><div class='line' id='LC350'>&nbsp;&nbsp;<span class="n">RCC</span><span class="o">-&gt;</span><span class="n">CR</span> <span class="o">|=</span> <span class="p">((</span><span class="kt">uint32_t</span><span class="p">)</span><span class="n">RCC_CR_HSEON</span><span class="p">);</span></div><div class='line' id='LC351'>&nbsp;</div><div class='line' id='LC352'>&nbsp;&nbsp;<span class="cm">/* Wait till HSE is ready and if Time out is reached exit */</span></div><div class='line' id='LC353'>&nbsp;&nbsp;<span class="k">do</span></div><div class='line' id='LC354'>&nbsp;&nbsp;<span class="p">{</span></div><div class='line' id='LC355'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">HSEStatus</span> <span class="o">=</span> <span class="n">RCC</span><span class="o">-&gt;</span><span class="n">CR</span> <span class="o">&amp;</span> <span class="n">RCC_CR_HSERDY</span><span class="p">;</span></div><div class='line' id='LC356'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">StartUpCounter</span><span class="o">++</span><span class="p">;</span></div><div class='line' id='LC357'>&nbsp;&nbsp;<span class="p">}</span> <span class="k">while</span><span class="p">((</span><span class="n">HSEStatus</span> <span class="o">==</span> <span class="mi">0</span><span class="p">)</span> <span class="o">&amp;&amp;</span> <span class="p">(</span><span class="n">StartUpCounter</span> <span class="o">!=</span> <span class="n">HSE_STARTUP_TIMEOUT</span><span class="p">));</span></div><div class='line' id='LC358'><br/></div><div class='line' id='LC359'>&nbsp;&nbsp;<span class="k">if</span> <span class="p">((</span><span class="n">RCC</span><span class="o">-&gt;</span><span class="n">CR</span> <span class="o">&amp;</span> <span class="n">RCC_CR_HSERDY</span><span class="p">)</span> <span class="o">!=</span> <span class="n">RESET</span><span class="p">)</span></div><div class='line' id='LC360'>&nbsp;&nbsp;<span class="p">{</span></div><div class='line' id='LC361'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">HSEStatus</span> <span class="o">=</span> <span class="p">(</span><span class="kt">uint32_t</span><span class="p">)</span><span class="mh">0x01</span><span class="p">;</span></div><div class='line' id='LC362'>&nbsp;&nbsp;<span class="p">}</span></div><div class='line' id='LC363'>&nbsp;&nbsp;<span class="k">else</span></div><div class='line' id='LC364'>&nbsp;&nbsp;<span class="p">{</span></div><div class='line' id='LC365'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">HSEStatus</span> <span class="o">=</span> <span class="p">(</span><span class="kt">uint32_t</span><span class="p">)</span><span class="mh">0x00</span><span class="p">;</span></div><div class='line' id='LC366'>&nbsp;&nbsp;<span class="p">}</span></div><div class='line' id='LC367'><br/></div><div class='line' id='LC368'>&nbsp;&nbsp;<span class="k">if</span> <span class="p">(</span><span class="n">HSEStatus</span> <span class="o">==</span> <span class="p">(</span><span class="kt">uint32_t</span><span class="p">)</span><span class="mh">0x01</span><span class="p">)</span></div><div class='line' id='LC369'>&nbsp;&nbsp;<span class="p">{</span></div><div class='line' id='LC370'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="cm">/* Select regulator voltage output Scale 1 mode, System frequency up to 168 MHz */</span></div><div class='line' id='LC371'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">RCC</span><span class="o">-&gt;</span><span class="n">APB1ENR</span> <span class="o">|=</span> <span class="n">RCC_APB1ENR_PWREN</span><span class="p">;</span></div><div class='line' id='LC372'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">PWR</span><span class="o">-&gt;</span><span class="n">CR</span> <span class="o">|=</span> <span class="n">PWR_CR_VOS</span><span class="p">;</span></div><div class='line' id='LC373'><br/></div><div class='line' id='LC374'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="cm">/* HCLK = SYSCLK / 1*/</span></div><div class='line' id='LC375'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">RCC</span><span class="o">-&gt;</span><span class="n">CFGR</span> <span class="o">|=</span> <span class="n">RCC_CFGR_HPRE_DIV1</span><span class="p">;</span></div><div class='line' id='LC376'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</div><div class='line' id='LC377'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="cm">/* PCLK2 = HCLK / 2*/</span></div><div class='line' id='LC378'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">RCC</span><span class="o">-&gt;</span><span class="n">CFGR</span> <span class="o">|=</span> <span class="n">RCC_CFGR_PPRE2_DIV2</span><span class="p">;</span></div><div class='line' id='LC379'>&nbsp;&nbsp;&nbsp;&nbsp;</div><div class='line' id='LC380'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="cm">/* PCLK1 = HCLK / 4*/</span></div><div class='line' id='LC381'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">RCC</span><span class="o">-&gt;</span><span class="n">CFGR</span> <span class="o">|=</span> <span class="n">RCC_CFGR_PPRE1_DIV4</span><span class="p">;</span></div><div class='line' id='LC382'><br/></div><div class='line' id='LC383'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="cm">/* Configure the main PLL */</span></div><div class='line' id='LC384'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">RCC</span><span class="o">-&gt;</span><span class="n">PLLCFGR</span> <span class="o">=</span> <span class="n">PLL_M</span> <span class="o">|</span> <span class="p">(</span><span class="n">PLL_N</span> <span class="o">&lt;&lt;</span> <span class="mi">6</span><span class="p">)</span> <span class="o">|</span> <span class="p">(((</span><span class="n">PLL_P</span> <span class="o">&gt;&gt;</span> <span class="mi">1</span><span class="p">)</span> <span class="o">-</span><span class="mi">1</span><span class="p">)</span> <span class="o">&lt;&lt;</span> <span class="mi">16</span><span class="p">)</span> <span class="o">|</span></div><div class='line' id='LC385'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">(</span><span class="n">RCC_PLLCFGR_PLLSRC_HSE</span><span class="p">)</span> <span class="o">|</span> <span class="p">(</span><span class="n">PLL_Q</span> <span class="o">&lt;&lt;</span> <span class="mi">24</span><span class="p">);</span></div><div class='line' id='LC386'><br/></div><div class='line' id='LC387'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="cm">/* Enable the main PLL */</span></div><div class='line' id='LC388'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">RCC</span><span class="o">-&gt;</span><span class="n">CR</span> <span class="o">|=</span> <span class="n">RCC_CR_PLLON</span><span class="p">;</span></div><div class='line' id='LC389'><br/></div><div class='line' id='LC390'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="cm">/* Wait till the main PLL is ready */</span></div><div class='line' id='LC391'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">while</span><span class="p">((</span><span class="n">RCC</span><span class="o">-&gt;</span><span class="n">CR</span> <span class="o">&amp;</span> <span class="n">RCC_CR_PLLRDY</span><span class="p">)</span> <span class="o">==</span> <span class="mi">0</span><span class="p">)</span></div><div class='line' id='LC392'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">{</span></div><div class='line' id='LC393'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">}</span></div><div class='line' id='LC394'>&nbsp;&nbsp;&nbsp;</div><div class='line' id='LC395'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="cm">/* Configure Flash prefetch, Instruction cache, Data cache and wait state */</span></div><div class='line' id='LC396'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">FLASH</span><span class="o">-&gt;</span><span class="n">ACR</span> <span class="o">=</span> <span class="n">FLASH_ACR_ICEN</span> <span class="o">|</span><span class="n">FLASH_ACR_DCEN</span> <span class="o">|</span><span class="n">FLASH_ACR_LATENCY_5WS</span><span class="p">;</span></div><div class='line' id='LC397'><br/></div><div class='line' id='LC398'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="cm">/* Select the main PLL as system clock source */</span></div><div class='line' id='LC399'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">RCC</span><span class="o">-&gt;</span><span class="n">CFGR</span> <span class="o">&amp;=</span> <span class="p">(</span><span class="kt">uint32_t</span><span class="p">)((</span><span class="kt">uint32_t</span><span class="p">)</span><span class="o">~</span><span class="p">(</span><span class="n">RCC_CFGR_SW</span><span class="p">));</span></div><div class='line' id='LC400'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">RCC</span><span class="o">-&gt;</span><span class="n">CFGR</span> <span class="o">|=</span> <span class="n">RCC_CFGR_SW_PLL</span><span class="p">;</span></div><div class='line' id='LC401'><br/></div><div class='line' id='LC402'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="cm">/* Wait till the main PLL is used as system clock source */</span></div><div class='line' id='LC403'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">while</span> <span class="p">((</span><span class="n">RCC</span><span class="o">-&gt;</span><span class="n">CFGR</span> <span class="o">&amp;</span> <span class="p">(</span><span class="kt">uint32_t</span><span class="p">)</span><span class="n">RCC_CFGR_SWS</span> <span class="p">)</span> <span class="o">!=</span> <span class="n">RCC_CFGR_SWS_PLL</span><span class="p">);</span></div><div class='line' id='LC404'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">{</span></div><div class='line' id='LC405'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">}</span></div><div class='line' id='LC406'>&nbsp;&nbsp;<span class="p">}</span></div><div class='line' id='LC407'>&nbsp;&nbsp;<span class="k">else</span></div><div class='line' id='LC408'>&nbsp;&nbsp;<span class="p">{</span> <span class="cm">/* If HSE fails to start-up, the application will have wrong clock</span></div><div class='line' id='LC409'><span class="cm">         configuration. User can add here some code to deal with this error */</span></div><div class='line' id='LC410'>&nbsp;&nbsp;<span class="p">}</span></div><div class='line' id='LC411'><br/></div><div class='line' id='LC412'><span class="p">}</span></div><div class='line' id='LC413'><br/></div><div class='line' id='LC414'><span class="cm">/**</span></div><div class='line' id='LC415'><span class="cm">  * @brief  Setup the external memory controller. Called in startup_stm32f4xx.s </span></div><div class='line' id='LC416'><span class="cm">  *          before jump to __main</span></div><div class='line' id='LC417'><span class="cm">  * @param  None</span></div><div class='line' id='LC418'><span class="cm">  * @retval None</span></div><div class='line' id='LC419'><span class="cm">  */</span> </div><div class='line' id='LC420'><span class="cp">#ifdef DATA_IN_ExtSRAM</span></div><div class='line' id='LC421'><span class="cm">/**</span></div><div class='line' id='LC422'><span class="cm">  * @brief  Setup the external memory controller.</span></div><div class='line' id='LC423'><span class="cm">  *         Called in startup_stm32f4xx.s before jump to main.</span></div><div class='line' id='LC424'><span class="cm">  *         This function configures the external SRAM mounted on STM324xG_EVAL board</span></div><div class='line' id='LC425'><span class="cm">  *         This SRAM will be used as program data memory (including heap and stack).</span></div><div class='line' id='LC426'><span class="cm">  * @param  None</span></div><div class='line' id='LC427'><span class="cm">  * @retval None</span></div><div class='line' id='LC428'><span class="cm">  */</span></div><div class='line' id='LC429'><span class="kt">void</span> <span class="nf">SystemInit_ExtMemCtl</span><span class="p">(</span><span class="kt">void</span><span class="p">)</span></div><div class='line' id='LC430'><span class="p">{</span></div><div class='line' id='LC431'><span class="cm">/*-- GPIOs Configuration -----------------------------------------------------*/</span></div><div class='line' id='LC432'><span class="cm">/*</span></div><div class='line' id='LC433'><span class="cm"> +-------------------+--------------------+------------------+------------------+</span></div><div class='line' id='LC434'><span class="cm"> +                       SRAM pins assignment                                   +</span></div><div class='line' id='LC435'><span class="cm"> +-------------------+--------------------+------------------+------------------+</span></div><div class='line' id='LC436'><span class="cm"> | PD0  &lt;-&gt; FSMC_D2  | PE0  &lt;-&gt; FSMC_NBL0 | PF0  &lt;-&gt; FSMC_A0 | PG0 &lt;-&gt; FSMC_A10 | </span></div><div class='line' id='LC437'><span class="cm"> | PD1  &lt;-&gt; FSMC_D3  | PE1  &lt;-&gt; FSMC_NBL1 | PF1  &lt;-&gt; FSMC_A1 | PG1 &lt;-&gt; FSMC_A11 | </span></div><div class='line' id='LC438'><span class="cm"> | PD4  &lt;-&gt; FSMC_NOE | PE3  &lt;-&gt; FSMC_A19  | PF2  &lt;-&gt; FSMC_A2 | PG2 &lt;-&gt; FSMC_A12 | </span></div><div class='line' id='LC439'><span class="cm"> | PD5  &lt;-&gt; FSMC_NWE | PE4  &lt;-&gt; FSMC_A20  | PF3  &lt;-&gt; FSMC_A3 | PG3 &lt;-&gt; FSMC_A13 | </span></div><div class='line' id='LC440'><span class="cm"> | PD8  &lt;-&gt; FSMC_D13 | PE7  &lt;-&gt; FSMC_D4   | PF4  &lt;-&gt; FSMC_A4 | PG4 &lt;-&gt; FSMC_A14 | </span></div><div class='line' id='LC441'><span class="cm"> | PD9  &lt;-&gt; FSMC_D14 | PE8  &lt;-&gt; FSMC_D5   | PF5  &lt;-&gt; FSMC_A5 | PG5 &lt;-&gt; FSMC_A15 | </span></div><div class='line' id='LC442'><span class="cm"> | PD10 &lt;-&gt; FSMC_D15 | PE9  &lt;-&gt; FSMC_D6   | PF12 &lt;-&gt; FSMC_A6 | PG9 &lt;-&gt; FSMC_NE2 | </span></div><div class='line' id='LC443'><span class="cm"> | PD11 &lt;-&gt; FSMC_A16 | PE10 &lt;-&gt; FSMC_D7   | PF13 &lt;-&gt; FSMC_A7 |------------------+</span></div><div class='line' id='LC444'><span class="cm"> | PD12 &lt;-&gt; FSMC_A17 | PE11 &lt;-&gt; FSMC_D8   | PF14 &lt;-&gt; FSMC_A8 | </span></div><div class='line' id='LC445'><span class="cm"> | PD13 &lt;-&gt; FSMC_A18 | PE12 &lt;-&gt; FSMC_D9   | PF15 &lt;-&gt; FSMC_A9 | </span></div><div class='line' id='LC446'><span class="cm"> | PD14 &lt;-&gt; FSMC_D0  | PE13 &lt;-&gt; FSMC_D10  |------------------+</span></div><div class='line' id='LC447'><span class="cm"> | PD15 &lt;-&gt; FSMC_D1  | PE14 &lt;-&gt; FSMC_D11  |</span></div><div class='line' id='LC448'><span class="cm"> |                   | PE15 &lt;-&gt; FSMC_D12  |</span></div><div class='line' id='LC449'><span class="cm"> +-------------------+--------------------+</span></div><div class='line' id='LC450'><span class="cm">*/</span></div><div class='line' id='LC451'>&nbsp;&nbsp;&nbsp;<span class="cm">/* Enable GPIOD, GPIOE, GPIOF and GPIOG interface clock */</span></div><div class='line' id='LC452'>&nbsp;&nbsp;<span class="n">RCC</span><span class="o">-&gt;</span><span class="n">AHB1ENR</span>   <span class="o">=</span> <span class="mh">0x00000078</span><span class="p">;</span></div><div class='line' id='LC453'>&nbsp;&nbsp;</div><div class='line' id='LC454'>&nbsp;&nbsp;<span class="cm">/* Connect PDx pins to FSMC Alternate function */</span></div><div class='line' id='LC455'>&nbsp;&nbsp;<span class="n">GPIOD</span><span class="o">-&gt;</span><span class="n">AFR</span><span class="p">[</span><span class="mi">0</span><span class="p">]</span>  <span class="o">=</span> <span class="mh">0x00cc00cc</span><span class="p">;</span></div><div class='line' id='LC456'>&nbsp;&nbsp;<span class="n">GPIOD</span><span class="o">-&gt;</span><span class="n">AFR</span><span class="p">[</span><span class="mi">1</span><span class="p">]</span>  <span class="o">=</span> <span class="mh">0xcc0ccccc</span><span class="p">;</span></div><div class='line' id='LC457'>&nbsp;&nbsp;<span class="cm">/* Configure PDx pins in Alternate function mode */</span>  </div><div class='line' id='LC458'>&nbsp;&nbsp;<span class="n">GPIOD</span><span class="o">-&gt;</span><span class="n">MODER</span>   <span class="o">=</span> <span class="mh">0xaaaa0a0a</span><span class="p">;</span></div><div class='line' id='LC459'>&nbsp;&nbsp;<span class="cm">/* Configure PDx pins speed to 100 MHz */</span>  </div><div class='line' id='LC460'>&nbsp;&nbsp;<span class="n">GPIOD</span><span class="o">-&gt;</span><span class="n">OSPEEDR</span> <span class="o">=</span> <span class="mh">0xffff0f0f</span><span class="p">;</span></div><div class='line' id='LC461'>&nbsp;&nbsp;<span class="cm">/* Configure PDx pins Output type to push-pull */</span>  </div><div class='line' id='LC462'>&nbsp;&nbsp;<span class="n">GPIOD</span><span class="o">-&gt;</span><span class="n">OTYPER</span>  <span class="o">=</span> <span class="mh">0x00000000</span><span class="p">;</span></div><div class='line' id='LC463'>&nbsp;&nbsp;<span class="cm">/* No pull-up, pull-down for PDx pins */</span> </div><div class='line' id='LC464'>&nbsp;&nbsp;<span class="n">GPIOD</span><span class="o">-&gt;</span><span class="n">PUPDR</span>   <span class="o">=</span> <span class="mh">0x00000000</span><span class="p">;</span></div><div class='line' id='LC465'><br/></div><div class='line' id='LC466'>&nbsp;&nbsp;<span class="cm">/* Connect PEx pins to FSMC Alternate function */</span></div><div class='line' id='LC467'>&nbsp;&nbsp;<span class="n">GPIOE</span><span class="o">-&gt;</span><span class="n">AFR</span><span class="p">[</span><span class="mi">0</span><span class="p">]</span>  <span class="o">=</span> <span class="mh">0xc00cc0cc</span><span class="p">;</span></div><div class='line' id='LC468'>&nbsp;&nbsp;<span class="n">GPIOE</span><span class="o">-&gt;</span><span class="n">AFR</span><span class="p">[</span><span class="mi">1</span><span class="p">]</span>  <span class="o">=</span> <span class="mh">0xcccccccc</span><span class="p">;</span></div><div class='line' id='LC469'>&nbsp;&nbsp;<span class="cm">/* Configure PEx pins in Alternate function mode */</span> </div><div class='line' id='LC470'>&nbsp;&nbsp;<span class="n">GPIOE</span><span class="o">-&gt;</span><span class="n">MODER</span>   <span class="o">=</span> <span class="mh">0xaaaa828a</span><span class="p">;</span></div><div class='line' id='LC471'>&nbsp;&nbsp;<span class="cm">/* Configure PEx pins speed to 100 MHz */</span> </div><div class='line' id='LC472'>&nbsp;&nbsp;<span class="n">GPIOE</span><span class="o">-&gt;</span><span class="n">OSPEEDR</span> <span class="o">=</span> <span class="mh">0xffffc3cf</span><span class="p">;</span></div><div class='line' id='LC473'>&nbsp;&nbsp;<span class="cm">/* Configure PEx pins Output type to push-pull */</span>  </div><div class='line' id='LC474'>&nbsp;&nbsp;<span class="n">GPIOE</span><span class="o">-&gt;</span><span class="n">OTYPER</span>  <span class="o">=</span> <span class="mh">0x00000000</span><span class="p">;</span></div><div class='line' id='LC475'>&nbsp;&nbsp;<span class="cm">/* No pull-up, pull-down for PEx pins */</span> </div><div class='line' id='LC476'>&nbsp;&nbsp;<span class="n">GPIOE</span><span class="o">-&gt;</span><span class="n">PUPDR</span>   <span class="o">=</span> <span class="mh">0x00000000</span><span class="p">;</span></div><div class='line' id='LC477'><br/></div><div class='line' id='LC478'>&nbsp;&nbsp;<span class="cm">/* Connect PFx pins to FSMC Alternate function */</span></div><div class='line' id='LC479'>&nbsp;&nbsp;<span class="n">GPIOF</span><span class="o">-&gt;</span><span class="n">AFR</span><span class="p">[</span><span class="mi">0</span><span class="p">]</span>  <span class="o">=</span> <span class="mh">0x00cccccc</span><span class="p">;</span></div><div class='line' id='LC480'>&nbsp;&nbsp;<span class="n">GPIOF</span><span class="o">-&gt;</span><span class="n">AFR</span><span class="p">[</span><span class="mi">1</span><span class="p">]</span>  <span class="o">=</span> <span class="mh">0xcccc0000</span><span class="p">;</span></div><div class='line' id='LC481'>&nbsp;&nbsp;<span class="cm">/* Configure PFx pins in Alternate function mode */</span>   </div><div class='line' id='LC482'>&nbsp;&nbsp;<span class="n">GPIOF</span><span class="o">-&gt;</span><span class="n">MODER</span>   <span class="o">=</span> <span class="mh">0xaa000aaa</span><span class="p">;</span></div><div class='line' id='LC483'>&nbsp;&nbsp;<span class="cm">/* Configure PFx pins speed to 100 MHz */</span> </div><div class='line' id='LC484'>&nbsp;&nbsp;<span class="n">GPIOF</span><span class="o">-&gt;</span><span class="n">OSPEEDR</span> <span class="o">=</span> <span class="mh">0xff000fff</span><span class="p">;</span></div><div class='line' id='LC485'>&nbsp;&nbsp;<span class="cm">/* Configure PFx pins Output type to push-pull */</span>  </div><div class='line' id='LC486'>&nbsp;&nbsp;<span class="n">GPIOF</span><span class="o">-&gt;</span><span class="n">OTYPER</span>  <span class="o">=</span> <span class="mh">0x00000000</span><span class="p">;</span></div><div class='line' id='LC487'>&nbsp;&nbsp;<span class="cm">/* No pull-up, pull-down for PFx pins */</span> </div><div class='line' id='LC488'>&nbsp;&nbsp;<span class="n">GPIOF</span><span class="o">-&gt;</span><span class="n">PUPDR</span>   <span class="o">=</span> <span class="mh">0x00000000</span><span class="p">;</span></div><div class='line' id='LC489'><br/></div><div class='line' id='LC490'>&nbsp;&nbsp;<span class="cm">/* Connect PGx pins to FSMC Alternate function */</span></div><div class='line' id='LC491'>&nbsp;&nbsp;<span class="n">GPIOG</span><span class="o">-&gt;</span><span class="n">AFR</span><span class="p">[</span><span class="mi">0</span><span class="p">]</span>  <span class="o">=</span> <span class="mh">0x00cccccc</span><span class="p">;</span></div><div class='line' id='LC492'>&nbsp;&nbsp;<span class="n">GPIOG</span><span class="o">-&gt;</span><span class="n">AFR</span><span class="p">[</span><span class="mi">1</span><span class="p">]</span>  <span class="o">=</span> <span class="mh">0x000000c0</span><span class="p">;</span></div><div class='line' id='LC493'>&nbsp;&nbsp;<span class="cm">/* Configure PGx pins in Alternate function mode */</span> </div><div class='line' id='LC494'>&nbsp;&nbsp;<span class="n">GPIOG</span><span class="o">-&gt;</span><span class="n">MODER</span>   <span class="o">=</span> <span class="mh">0x00080aaa</span><span class="p">;</span></div><div class='line' id='LC495'>&nbsp;&nbsp;<span class="cm">/* Configure PGx pins speed to 100 MHz */</span> </div><div class='line' id='LC496'>&nbsp;&nbsp;<span class="n">GPIOG</span><span class="o">-&gt;</span><span class="n">OSPEEDR</span> <span class="o">=</span> <span class="mh">0x000c0fff</span><span class="p">;</span></div><div class='line' id='LC497'>&nbsp;&nbsp;<span class="cm">/* Configure PGx pins Output type to push-pull */</span>  </div><div class='line' id='LC498'>&nbsp;&nbsp;<span class="n">GPIOG</span><span class="o">-&gt;</span><span class="n">OTYPER</span>  <span class="o">=</span> <span class="mh">0x00000000</span><span class="p">;</span></div><div class='line' id='LC499'>&nbsp;&nbsp;<span class="cm">/* No pull-up, pull-down for PGx pins */</span> </div><div class='line' id='LC500'>&nbsp;&nbsp;<span class="n">GPIOG</span><span class="o">-&gt;</span><span class="n">PUPDR</span>   <span class="o">=</span> <span class="mh">0x00000000</span><span class="p">;</span></div><div class='line' id='LC501'>&nbsp;&nbsp;</div><div class='line' id='LC502'><span class="cm">/*-- FSMC Configuration ------------------------------------------------------*/</span></div><div class='line' id='LC503'>&nbsp;&nbsp;<span class="cm">/* Enable the FSMC interface clock */</span></div><div class='line' id='LC504'>&nbsp;&nbsp;<span class="n">RCC</span><span class="o">-&gt;</span><span class="n">AHB3ENR</span>         <span class="o">=</span> <span class="mh">0x00000001</span><span class="p">;</span></div><div class='line' id='LC505'><br/></div><div class='line' id='LC506'>&nbsp;&nbsp;<span class="cm">/* Configure and enable Bank1_SRAM2 */</span></div><div class='line' id='LC507'>&nbsp;&nbsp;<span class="n">FSMC_Bank1</span><span class="o">-&gt;</span><span class="n">BTCR</span><span class="p">[</span><span class="mi">2</span><span class="p">]</span>  <span class="o">=</span> <span class="mh">0x00001015</span><span class="p">;</span></div><div class='line' id='LC508'>&nbsp;&nbsp;<span class="n">FSMC_Bank1</span><span class="o">-&gt;</span><span class="n">BTCR</span><span class="p">[</span><span class="mi">3</span><span class="p">]</span>  <span class="o">=</span> <span class="mh">0x00010603</span><span class="p">;</span></div><div class='line' id='LC509'>&nbsp;&nbsp;<span class="n">FSMC_Bank1E</span><span class="o">-&gt;</span><span class="n">BWTR</span><span class="p">[</span><span class="mi">2</span><span class="p">]</span> <span class="o">=</span> <span class="mh">0x0fffffff</span><span class="p">;</span></div><div class='line' id='LC510'><span class="cm">/*</span></div><div class='line' id='LC511'><span class="cm">  Bank1_SRAM2 is configured as follow:</span></div><div class='line' id='LC512'><br/></div><div class='line' id='LC513'><span class="cm">  p.FSMC_AddressSetupTime = 3;</span></div><div class='line' id='LC514'><span class="cm">  p.FSMC_AddressHoldTime = 0;</span></div><div class='line' id='LC515'><span class="cm">  p.FSMC_DataSetupTime = 6;</span></div><div class='line' id='LC516'><span class="cm">  p.FSMC_BusTurnAroundDuration = 1;</span></div><div class='line' id='LC517'><span class="cm">  p.FSMC_CLKDivision = 0;</span></div><div class='line' id='LC518'><span class="cm">  p.FSMC_DataLatency = 0;</span></div><div class='line' id='LC519'><span class="cm">  p.FSMC_AccessMode = FSMC_AccessMode_A;</span></div><div class='line' id='LC520'><br/></div><div class='line' id='LC521'><span class="cm">  FSMC_NORSRAMInitStructure.FSMC_Bank = FSMC_Bank1_NORSRAM2;</span></div><div class='line' id='LC522'><span class="cm">  FSMC_NORSRAMInitStructure.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable;</span></div><div class='line' id='LC523'><span class="cm">  FSMC_NORSRAMInitStructure.FSMC_MemoryType = FSMC_MemoryType_PSRAM;</span></div><div class='line' id='LC524'><span class="cm">  FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;</span></div><div class='line' id='LC525'><span class="cm">  FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode = FSMC_BurstAccessMode_Disable;</span></div><div class='line' id='LC526'><span class="cm">  FSMC_NORSRAMInitStructure.FSMC_AsynchronousWait = FSMC_AsynchronousWait_Disable;  </span></div><div class='line' id='LC527'><span class="cm">  FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;</span></div><div class='line' id='LC528'><span class="cm">  FSMC_NORSRAMInitStructure.FSMC_WrapMode = FSMC_WrapMode_Disable;</span></div><div class='line' id='LC529'><span class="cm">  FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;</span></div><div class='line' id='LC530'><span class="cm">  FSMC_NORSRAMInitStructure.FSMC_WriteOperation = FSMC_WriteOperation_Enable;</span></div><div class='line' id='LC531'><span class="cm">  FSMC_NORSRAMInitStructure.FSMC_WaitSignal = FSMC_WaitSignal_Disable;</span></div><div class='line' id='LC532'><span class="cm">  FSMC_NORSRAMInitStructure.FSMC_ExtendedMode = FSMC_ExtendedMode_Disable;</span></div><div class='line' id='LC533'><span class="cm">  FSMC_NORSRAMInitStructure.FSMC_WriteBurst = FSMC_WriteBurst_Disable;</span></div><div class='line' id='LC534'><span class="cm">  FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = &amp;p;</span></div><div class='line' id='LC535'><span class="cm">  FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct = &amp;p;</span></div><div class='line' id='LC536'><span class="cm">*/</span></div><div class='line' id='LC537'>&nbsp;&nbsp;</div><div class='line' id='LC538'><span class="p">}</span></div><div class='line' id='LC539'><span class="cp">#endif </span><span class="cm">/* DATA_IN_ExtSRAM */</span><span class="cp"></span></div><div class='line' id='LC540'><br/></div><div class='line' id='LC541'><br/></div><div class='line' id='LC542'><span class="cm">/**</span></div><div class='line' id='LC543'><span class="cm">  * @}</span></div><div class='line' id='LC544'><span class="cm">  */</span></div><div class='line' id='LC545'><br/></div><div class='line' id='LC546'><span class="cm">/**</span></div><div class='line' id='LC547'><span class="cm">  * @}</span></div><div class='line' id='LC548'><span class="cm">  */</span></div><div class='line' id='LC549'>&nbsp;&nbsp;</div><div class='line' id='LC550'><span class="cm">/**</span></div><div class='line' id='LC551'><span class="cm">  * @}</span></div><div class='line' id='LC552'><span class="cm">  */</span>    </div><div class='line' id='LC553'><span class="cm">/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/</span></div></pre></div>
          </td>
        </tr>
      </table>
  </div>

  </div>
</div>

<a href="#jump-to-line" rel="facebox[.linejump]" data-hotkey="l" class="js-jump-to-line" style="display:none">Jump to Line</a>
<div id="jump-to-line" style="display:none">
  <form accept-charset="UTF-8" class="js-jump-to-line-form">
    <input class="linejump-input js-jump-to-line-field" type="text" placeholder="Jump to line&hellip;" autofocus>
    <button type="submit" class="button">Go</button>
  </form>
</div>

        </div>

      </div><!-- /.repo-container -->
      <div class="modal-backdrop"></div>
    </div><!-- /.container -->
  </div><!-- /.site -->


    </div><!-- /.wrapper -->

      <div class="container">
  <div class="site-footer">
    <ul class="site-footer-links right">
      <li><a href="https://status.github.com/">Status</a></li>
      <li><a href="http://developer.github.com">API</a></li>
      <li><a href="http://training.github.com">Training</a></li>
      <li><a href="http://shop.github.com">Shop</a></li>
      <li><a href="/blog">Blog</a></li>
      <li><a href="/about">About</a></li>

    </ul>

    <a href="/">
      <span class="mega-octicon octicon-mark-github"></span>
    </a>

    <ul class="site-footer-links">
      <li>&copy; 2013 <span title="0.17504s from fe1.rs.github.com">GitHub</span>, Inc.</li>
        <li><a href="/site/terms">Terms</a></li>
        <li><a href="/site/privacy">Privacy</a></li>
        <li><a href="/security">Security</a></li>
        <li><a href="/contact">Contact</a></li>
    </ul>
  </div><!-- /.site-footer -->
</div><!-- /.container -->


    <div class="fullscreen-overlay js-fullscreen-overlay" id="fullscreen_overlay">
  <div class="fullscreen-container js-fullscreen-container">
    <div class="textarea-wrap">
      <textarea name="fullscreen-contents" id="fullscreen-contents" class="js-fullscreen-contents" placeholder="" data-suggester="fullscreen_suggester"></textarea>
          <div class="suggester-container">
              <div class="suggester fullscreen-suggester js-navigation-container" id="fullscreen_suggester"
                 data-url="/JekaKey/Fatarminator/suggestions/commit">
              </div>
          </div>
    </div>
  </div>
  <div class="fullscreen-sidebar">
    <a href="#" class="exit-fullscreen js-exit-fullscreen tooltipped leftwards" title="Exit Zen Mode">
      <span class="mega-octicon octicon-screen-normal"></span>
    </a>
    <a href="#" class="theme-switcher js-theme-switcher tooltipped leftwards"
      title="Switch themes">
      <span class="octicon octicon-color-mode"></span>
    </a>
  </div>
</div>



    <div id="ajax-error-message" class="flash flash-error">
      <span class="octicon octicon-alert"></span>
      <a href="#" class="octicon octicon-remove-close close ajax-error-dismiss"></a>
      Something went wrong with that request. Please try again.
    </div>

    
  </body>
</html>

