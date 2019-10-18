for repo in xenclient-oe.git manager.git toolstack-data.git idl.git xctools.git;do #Add/remove required git repo's
    rm -rf $repo;
    git clone --bare https://github.com/OpenXT/$repo $repo; #Give proper github website
done
