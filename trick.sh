for repo in xenclient-oe.git manager.git toolstack-data.git idl.git xctools.git;do #Add/remove required git repo's
    rm -rf $repo;
    git clone --bare https://github.com/mahantesh-ais/$repo $repo; #Give proper github website
    cd $repo; 
    git branch tmp; 
    git symbolic-ref HEAD refs/heads/tmp; 
    git branch -m master originalmaster; 
    if [ "x$repo" = "xtoolstack-data.git" ]; then
        git branch master rm_nwds_add_nic;
    elif [ "x$repo" = "xxenclient-oe.git" ]; then
        git branch master nm_rpcb;
    elif [ "x$repo" = "xxctools.git" ]; then
        git branch master rpcb;
    else
        git branch master rm_nwd_nws; # replace rm_nwd_nws with required branch 
    fi
    git symbolic-ref HEAD refs/heads/master; 
    cd - > /dev/null;
done
