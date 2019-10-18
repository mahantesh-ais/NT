for repo in manager.git idl.git;do #Add/remove required git repo's
    rm -rf $repo;
    git clone --bare https://github.com/mahantesh-ais/$repo $repo; #Give proper github website
    cd $repo; 
    git branch tmp; 
    git symbolic-ref HEAD refs/heads/tmp; 
    git branch -m master originalmaster; 
    git branch master ahci-support; # replace rm_nwd_nws with required branch 
    git symbolic-ref HEAD refs/heads/master; 
    cd - > /dev/null;
done
